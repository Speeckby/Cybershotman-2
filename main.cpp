#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

#include "include/helper.h"
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
	int score;

    // initialisation de la partie graphique via GRRLIB
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

	// on demande les informations sur les boutons, la caméra et les accéléromètres
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);

	vec3w_t accel;
	orient_t orien;
	expansion_t exp;
	ir_t ir;

	GRRLIB_texImg* cursor = GRRLIB_LoadTextureFromFile("sd:/survivor/curseur.png");
    GRRLIB_SetMidHandle(cursor, true);

	const GRRLIB_texImg* img_menu[9];

	img_menu[0] = GRRLIB_LoadTextureFromFile("sd:/survivor/player/blue.png");
    img_menu[1] = GRRLIB_LoadTextureFromFile("sd:/survivor/player/purple.png");
    img_menu[2] = GRRLIB_LoadTextureFromFile("sd:/survivor/player/white.png");
    img_menu[3] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/title.png");
    img_menu[4] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/off.png");
    img_menu[5] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/play.png");
    img_menu[6] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/arrow_left.png");
    img_menu[7] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/arrow_right.png");
    img_menu[8] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu/background.png");

    GRRLIB_texImg* tuiles_perso_purple = GRRLIB_LoadTextureFromFile("sd:/survivor/player/purple_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso_purple, 32,32,0);
    GRRLIB_SetMidHandle(tuiles_perso_purple, true);

    GRRLIB_texImg* tuiles_perso_blue = GRRLIB_LoadTextureFromFile("sd:/survivor/player/blue_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso_blue, 32,32,0);
    GRRLIB_SetMidHandle(tuiles_perso_blue, true);

    GRRLIB_texImg* tuiles_perso_white = GRRLIB_LoadTextureFromFile("sd:/survivor/player/white_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso_white, 32,32,0);
    GRRLIB_SetMidHandle(tuiles_perso_white, true);


    GRRLIB_texImg* img_perso[3];

    img_perso[0] = tuiles_perso_blue;
    img_perso[1] = tuiles_perso_purple;
    img_perso[2] = tuiles_perso_white;

	Caracteristique perso_carac = Caracteristique(100,200,100,15,1,cursor);


    Perso * perso = new Perso(&perso_carac);
    GRRLIB_texImg* tuiles_carte = GRRLIB_LoadTextureFromFile("sd:/survivor/maps/1.png");
    GRRLIB_InitTileSet(tuiles_carte, 16,16, 0);
    GRRLIB_SetMidHandle(tuiles_carte, true);


    GRRLIB_texImg* projectile_img = GRRLIB_LoadTextureFromFile("sd:/survivor/missile.png");
    GRRLIB_InitTileSet(projectile_img,28,28,0);
    GRRLIB_SetMidHandle(projectile_img, true);

    GRRLIB_texImg* blob = GRRLIB_LoadTextureFromFile("sd:/survivor/monstre/blob.png");
    GRRLIB_InitTileSet(blob, 32,32, 0);
    GRRLIB_SetMidHandle(blob, true);


    GRRLIB_ttfFont * police = GRRLIB_LoadTTFFromFile("sd:/survivor/font.ttf");
    score = 0;
    Monstre * monstre = new Monstre(1,perso->donnees->m_x,perso->donnees->m_y, blob);

    Menu menus = Menu();

    bool menu_bool = true;
    int t = 0;
    int skin_add = 0;
    int var_bg = 0;

    // On défini l'espace de stockage des projectiles

    vector <Projectile *> projectiles;

	// boucle qui continuera tant que l'application n'est pas arrêtée
	while(1)
	{
		//récupération des informations des contrôleurs
		WPAD_ScanPads();

		// On scane la manette et attribue les valeurs aux variables
        WPAD_Accel(WPAD_CHAN_0, &accel);
	    WPAD_Orientation(WPAD_CHAN_0, &orien);
        WPAD_IR(WPAD_CHAN_0, &ir);
        WPAD_Expansion(WPAD_CHAN_0, &exp);
        //variable pressed remplit avec l'état des boutons du controleur 0
		u32 held = WPAD_ButtonsHeld(WPAD_CHAN_0);
		u32 down = WPAD_ButtonsDown(WPAD_CHAN_0);
		// On sort de la boucle et donc on quitte le programme et on retourne au launcher si le bouton home est appuyé

		GRRLIB_FillScreen(0x000000);
		if ( down & WPAD_BUTTON_HOME ) {
            if (menu_bool) exit(0);
            else  {
                menu_bool = true;
                perso->reset();
                projectiles.clear();
            }
		};
        if (var_bg == 0){GRRLIB_FillScreen(0x000000FF);
        }
        if (var_bg == 1){GRRLIB_FillScreen(0x211b27FF);
        }
		VIDEO_WaitVSync();

		if (menu_bool) {
            menu_bool = menus.menu_index(ir, held, down, img_menu, img_perso, perso);
		}
		else {
            score+=1%100;
		    std::unordered_map<std::string, bool> states = getButton(held, down);
            std::string score_str = std::to_string(score);
            const char* score_char = score_str.c_str();
            var_bg = 1;
            int x_map = 100-perso->donnees->m_x*2;
            int y_map = 100-perso->donnees->m_y*2;
            int skin = perso->changement_sprite(exp);
            perso->deplacer_perso(exp);
            afficher_map(exp, tuiles_carte, 100-perso->donnees->m_x*2, 100-perso->donnees->m_y*2);
            if (skin > 1){
                t ++;
                if (t%5 == 0){
                    skin_add++;
                }
            }
            else{
                t = 0;
                skin_add = 0;
                }
            if (skin_add == 4){skin_add = 0;}
            perso->afficher_perso(skin+skin_add);
            monstre -> deplacer_monstre(exp,perso, x_map, y_map);

            if (states["A"] & (projectiles.size() < 5)) projectiles.push_back(new Projectile(perso->donnees->m_x,perso->donnees->m_y, ir.x, ir.y, projectile_img));
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
            GRRLIB_PrintfTTF(100, 100, police, score_char, 300, 0x000000FF);

		}
        GRRLIB_DrawImg(ir.x ,ir.y, cursor, 0, 1, 1, 0xFFFFFFFF);

		GRRLIB_Render();
		// On attend la prochaine trame à dessiner

	}
	// valeur de retour, 0 = tout s'est bien passé
	return 0;
}
