#include <stdio.h>
#include <stdlib.h>
#include <set>

#include "include/Caracteristique.h"
#include "include/Perso.h"
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include "include/Menu.h"
#include "include/Map.h"
#include "WiiNetDbg.h"

// le programme principal, fonction qui sera exécutée au lancement de l'application
int main(int argc, char **argv)
{

    // déclaration d'une variable pour fermer l'application

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

	const GRRLIB_texImg* img_menu[8];

	img_menu[0] = GRRLIB_LoadTextureFromFile("sd:/survivor/player/blue.png");
    img_menu[1] = GRRLIB_LoadTextureFromFile("sd:/survivor/player/purple.png");
    img_menu[2] = GRRLIB_LoadTextureFromFile("sd:/survivor/title.png");
    img_menu[3] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu_off.png");
    img_menu[4] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu_play.png");
    img_menu[5] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu_arrow_left.png");
    img_menu[6] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu_arrow_right.png");
    img_menu[7] = GRRLIB_LoadTextureFromFile("sd:/survivor/menu_background.png");

    GRRLIB_texImg* tuiles_perso = GRRLIB_LoadTextureFromFile("sd:/survivor/player/purple_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso, 32,32,0);
	Caracteristique perso_carac = Caracteristique(100,200,100,15,1,tuiles_perso);

    Perso perso = Perso(&perso_carac);
    perso.init_perso();
    GRRLIB_texImg* tuiles_carte = GRRLIB_LoadTextureFromFile("sd:/survivor/maps/1.png");
    GRRLIB_InitTileSet(tuiles_carte, 16,16, 0);

    GRRLIB_texImg* projectile_img = GRRLIB_LoadTextureFromFile("sd:/survivor/projectile.png");

    Menu menus = Menu();

    bool menu_bool = true;

    // On défini l'espace de stockage des projectiles
    set <Projectile *> projectiles;

	// boucle qui continuera tant que l'application n'est pas arrêtée
	while(1)
	{

		//récupération des informations des contrôleurs
		WPAD_ScanPads();
		//variable pressed remplit avec l'état des boutons du controleur 0
		u32 held = WPAD_ButtonsHeld(WPAD_CHAN_0);
		u32 down = WPAD_ButtonsDown(WPAD_CHAN_0);
		// On scane la manette et attribue les valeurs aux variables
        WPAD_Accel(WPAD_CHAN_0, &accel);
	    WPAD_Orientation(WPAD_CHAN_0, &orien);
        WPAD_IR(WPAD_CHAN_0, &ir);
        WPAD_Expansion(WPAD_CHAN_0, &exp);

		// On sort de la boucle et donc on quitte le programme et on retourne au launcher si le bouton home est appuyé
		if ( down & WPAD_BUTTON_HOME ) {
            if (menu_bool) exit(0);
            else menu_bool = true;
		};


		if (menu_bool) {
           menu_bool = menus.menu_index(ir, held, down, img_menu);
		}
		else {
            if (perso.donnees->m_y >= 16) {
                perso.deplacer_perso(exp);
            } else {
                perso.donnees->m_y+=1;
            }

            //if (perso.donnees->m_x<14;73 - 357;147 - 15;254 - 357;424) essaie de détection de collision
            afficher_map(exp, tuiles_carte, 100-perso.donnees->m_x*2, 100-perso.donnees->m_y*2);
            perso.afficher_perso();
            for (Projectile * projectile : projectiles) {
                projectile->updatePos();
                projectile->display();
                if (projectile->isHidden()) {
                    delete projectile;
                }
            }
		}
        GRRLIB_DrawImg(ir.x ,ir.y, cursor, 0, 1, 1, 0xFFFFFFFF);

		GRRLIB_Render();
		// On attend la prochaine trame à dessiner
		VIDEO_WaitVSync();
	}
	// valeur de retour, 0 = tout s'est bien passé
	return 0;
}
