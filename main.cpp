#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <ctime> // Pour la fonction time
using namespace std;

#include "include/Caracteristique.h"
#include "include/Perso.h"
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include "include/Menu.h"
#include "include/Map.h"
#include "include/Projectile.h"
#include "include/Monstre.h"

// le programme principal, fonction qui sera exécutée au lancement de l'application
int main(int argc, char **argv)
{
    // déclaration d'une variable pour fermer l'application

    // initialisation de la partie graphique via GRRLIB
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    // on demande les informations sur les boutons, la caméra et les accéléromètres
    WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);

    vec3w_t accel;
    orient_t orien;
    expansion_t exp;
    ir_t ir;
    int score;
    bool verif;
    GRRLIB_texImg* img_monstre;

    GRRLIB_texImg* cursor = GRRLIB_LoadTextureFromFile("sd:/survivor/curseur.png");
    GRRLIB_SetMidHandle(cursor, true);

    GRRLIB_ttfFont* police = GRRLIB_LoadTTFFromFile("sd:/survivor/font.ttf");
    score = 0;

    GRRLIB_texImg* tuiles_perso_purple = GRRLIB_LoadTextureFromFile("sd:/survivor/player/purple_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso_purple, 32, 32, 0);
    GRRLIB_SetMidHandle(tuiles_perso_purple, true);

    GRRLIB_texImg* tuiles_perso_blue = GRRLIB_LoadTextureFromFile("sd:/survivor/player/blue_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso_blue, 32, 32, 0);
    GRRLIB_SetMidHandle(tuiles_perso_blue, true);

    GRRLIB_texImg* tuiles_perso_white = GRRLIB_LoadTextureFromFile("sd:/survivor/player/white_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso_white, 32,32,0);
    GRRLIB_SetMidHandle(tuiles_perso_white, true);

    GRRLIB_texImg* barre_vie = GRRLIB_LoadTextureFromFile("sd:/survivor/life_bar.png");
    GRRLIB_texImg* coeur = GRRLIB_LoadTextureFromFile("sd:/survivor/life_heart.png");
    GRRLIB_texImg* peiou = GRRLIB_LoadTextureFromFile("sd:/survivor/monstre/easteregg.png");
    GRRLIB_SetMidHandle(peiou, true);

    const GRRLIB_texImg* img_menu[8];

    img_menu[0] = GRRLIB_LoadTextureFromFile("sd:/survivor/player/blue.png");
    img_menu[1] = GRRLIB_LoadTextureFromFile("sd:/survivor/player/purple.png");
    img_menu[2] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/title.png");
    img_menu[3] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/off.png");
    img_menu[4] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/play.png");
    img_menu[5] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/arrow_left.png");
    img_menu[6] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/arrow_right.png");
    img_menu[7] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/background.png");

    GRRLIB_texImg* img_perso[2];

    img_perso[0] = tuiles_perso_blue;
    img_perso[1] = tuiles_perso_purple;

    Caracteristique perso_carac = Caracteristique(100, 200, 100, 20, 1, cursor);
    Perso* perso = new Perso(&perso_carac);

    GRRLIB_texImg* tuiles_carte = GRRLIB_LoadTextureFromFile("sd:/survivor/maps/1.png");
    GRRLIB_InitTileSet(tuiles_carte, 16, 16, 0);
    GRRLIB_SetMidHandle(tuiles_carte, true);

    GRRLIB_texImg* blob = GRRLIB_LoadTextureFromFile("sd:/survivor/monstre/blob.png");
    GRRLIB_InitTileSet(blob, 32, 32, 0);
    GRRLIB_SetMidHandle(blob, true);

    GRRLIB_texImg* squelette = GRRLIB_LoadTextureFromFile("sd:/survivor/monstre/squelette.png");
    GRRLIB_InitTileSet(squelette, 32, 32, 0);
    GRRLIB_SetMidHandle(squelette, true);

    GRRLIB_texImg* escargot = GRRLIB_LoadTextureFromFile("sd:/survivor/monstre/escargot.png");
    GRRLIB_InitTileSet(escargot, 32, 32, 0);
    GRRLIB_SetMidHandle(escargot, true);

    GRRLIB_texImg* projectile_img = GRRLIB_LoadTextureFromFile("sd:/survivor/missile.png");
    GRRLIB_InitTileSet(projectile_img,28,28,0);
    GRRLIB_SetMidHandle(projectile_img, true);

    GRRLIB_texImg* death_img = GRRLIB_LoadTextureFromFile("sd:/survivor/death_sprite3.png");
    GRRLIB_InitTileSet(death_img,64,64,0);
    GRRLIB_SetMidHandle(death_img, true);

    // Utiliser un vector pour stocker les monstres
    vector<Monstre*> monstres;

    Menu menus = Menu();

    bool menu_bool = true;
    int t = 0;
    int skin_add = 0;
    int var_bg = 0;
    // On défini l'espace de stockage des projectiles
    vector <Projectile *> projectiles;

    // Variables pour la gestion du temps
    //time_t start_time = time(0);
    //time_t current_time;
    int rand_nbr;
    int temps = 0;
    int New_temps = 10;
    int chargeur=100;
    int t_death=0;
    int t_death_count=0;
    int var_death=0;


    // boucle qui continuera tant que l'application n'est pas arrêtée
    while (1)
    {
        //récupération des informations des contrôleurs
        WPAD_ScanPads();
        GRRLIB_DrawImg(ir.x, ir.y, cursor, 0, 2, 2, 0xFFFFFFFF);
        temps+=1;
        if (chargeur<100){
            if (temps%2==0){
                chargeur+=1;
            }
        }

        // On scane la manette et attribue les valeurs aux variables
        WPAD_Accel(WPAD_CHAN_0, &accel);
        WPAD_Orientation(WPAD_CHAN_0, &orien);
        WPAD_IR(WPAD_CHAN_0, &ir);
        WPAD_Expansion(WPAD_CHAN_0, &exp);
        //variable pressed remplit avec l'état des boutons du controleur 0
        u32 held = WPAD_ButtonsHeld(WPAD_CHAN_0);
        u32 down = WPAD_ButtonsDown(WPAD_CHAN_0);
        // On sort de la boucle et donc on quitte le programme et on retourne au launcher si le bouton home est appuyé
        if (down & WPAD_BUTTON_HOME) {
            if (menu_bool) exit(0);
            else {
                menu_bool = true;
                // Supprimer tous les monstres
                for (auto monstre : monstres) {
                    delete monstre;
                }
                monstres.clear();
                projectiles.clear();
            }
        }
        // Mettre à jour les projectiles et vérifier les collisions
        vector<Projectile*>::iterator it = projectiles.begin();

        while (it != projectiles.end()) {
            (*it)->updatePos(exp);
            bool projectileDestroyed = false;

            // Vérifier la collision du projectile avec chaque monstre
            for (auto monstre = monstres.begin(); monstre != monstres.end(); ++monstre) {
                if ((*it)->collision(*monstre)) {
                    delete *monstre;
                    monstres.erase(monstre);
                    projectileDestroyed = true;
                    break;
                }
            }

            if (projectileDestroyed || (*it)->isHidden()) {
                delete *it;
                it = projectiles.erase(it);
            } else {
                (*it)->display();
                ++it;
            }
        }

        if (var_bg == 0) {
            GRRLIB_FillScreen(0x000000FF);
        }
        if (var_bg == 1) {
            GRRLIB_FillScreen(0x211b27FF);
        }
        VIDEO_WaitVSync();

        if (menu_bool) {
            var_bg = 0;
            perso_carac = Caracteristique(100, 200, 100, 20, 1, cursor);
            menu_bool = menus.menu_index(ir, held, down, img_menu, img_perso, perso);
        }
        else {
            std::unordered_map<std::string, bool> states = getButton(held, down);
            if (temps%5==0){
                ++score;
            }
            std::string score_str = std::to_string(score);
            const char* score_char = score_str.c_str();

            var_bg = 1;
            int x_map = 100 - perso->donnees->m_x * 2;
            int y_map = 100 - perso->donnees->m_y * 2;
            int skin = perso->changement_sprite(exp);
            perso->deplacer_perso(exp);
            afficher_map(exp, tuiles_carte, 100 - perso->donnees->m_x * 2, 100 - perso->donnees->m_y * 2);
            if (states["A"] & (projectiles.size() < 5)){
                if (chargeur>=10){
                projectiles.push_back(new Projectile(perso->donnees->m_x,perso->donnees->m_y, ir.x, ir.y, projectile_img));
                chargeur-=10;
                }
            }
            vector <Projectile *>::iterator it = projectiles.begin();

            while (it < projectiles.end()) {
                (*it)->updatePos(exp);
                if ((*it)->isHidden()) {
                    vector <Projectile *>::iterator itremove = it;
                    ++it;
                    delete *itremove;
                    projectiles.erase(itremove);
                }
                else {
                    (*it)->display();
                    ++it;
                }
            }
            if (skin > 1) {
                t++;
                if (t % 5 == 0) {
                    skin_add++;
                }
            }
            else {
                t = 0;
                skin_add = 0;
            }
            if (skin_add == 4) { skin_add = 0; }
            perso->afficher_perso(skin + skin_add);

            // Ajouter un monstre toutes les 0.3 secondes
            //current_time = time(0);

            rand_nbr = rand() % 3 + 1;
            if (rand_nbr == 1){
                img_monstre = escargot;
            }else if (rand_nbr == 2){
                img_monstre = squelette;
            }else{
                img_monstre = blob;
            }
            if (temps%10000==0) {
                New_temps-=1;
            }
            if (monstres.size()<50){
                if (temps%New_temps==0) {
                monstres.push_back(new Monstre(1, perso->donnees->m_x, perso->donnees->m_y, img_monstre));
                //start_time = current_time;
            }}

            // Déplacer et afficher tous les monstres
            for (auto monstre : monstres) {
                monstre->deplacer_monstre(exp, perso, x_map, y_map);
                verif = monstre->collision_monstre(perso);
                if (verif == true) {
                    perso->perdre_vie();
                }

                // Vérifier les collisions entre monstres
                for (auto autre_monstre : monstres) {
                    if (monstre != autre_monstre) {
                        monstre->collision_intermonstre(autre_monstre);
                    }
                }
            }

            if (perso->est_mort()) {
                // Supprimer tous les monstres
                for (auto monstre : monstres) {
                    delete monstre;
                }
                monstres.clear();
                //animation de mort
                GRRLIB_FillScreen(0x000000FF);
                t_death++;
                GRRLIB_DrawTile(300,220, death_img, 0, 2, 2, 0xFFFFFFFF, var_death);
                if (t_death%2 == 0){
                    t_death_count++;
                }
                if (var_death <8){
                    if (t_death_count == 1){
                        var_death++;
                        t_death_count = 0;}
                }
                if (var_death ==8){
                    if (t_death_count == 4){
                        var_death++;
                        t_death_count = 0;}
                }
                if (var_death >8 && var_death <12){
                    if (t_death_count == 1){
                        var_death++;
                        t_death_count = 0;}
                }
                if (var_death ==12){
                    if (t_death_count == 4){
                        var_death++;
                        t_death_count = 0;}
                }
                if (var_death >12 && var_death <17){
                    if (t_death_count == 1){
                        var_death++;
                        t_death_count = 0;}
                }
                if (var_death == 17){
                    if (t_death_count == 10){
                        t_death_count = 0;
                        var_death = 0;
                        GRRLIB_DrawImg(320, 220, peiou, 0, 1, 1, 0xFFFFFFFF);
                        menu_bool = true;}
                }
            }
            if (perso->donnees->m_hp!=0){
                GRRLIB_DrawImg(268, 442, barre_vie, 0, 1, 1, 0xFFFFFFFF);
                GRRLIB_Rectangle(280, 449, perso->donnees->m_hp * 3.54, 18, 0x00FF00FF, true);
                GRRLIB_DrawImg(255, 435, coeur, 0, 1.5, 1.5, 0xFFFFFFFF);
                GRRLIB_Rectangle(280, 420, chargeur * 3.5, 8, 0xFF0000FF, true);
                GRRLIB_PrintfTTF(280, 20, police, score_char, 30, 0x000000FF);
            }

        }
        GRRLIB_DrawImg(ir.x, ir.y, cursor, 0,2,2, 0xFF0000FF);
        GRRLIB_Render();
        // On attend la prochaine trame à dessiner
    }
    // valeur de retour, 0 = tout s'est bien passé
    return 0;
}
