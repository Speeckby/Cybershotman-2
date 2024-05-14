#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>

#include <grrlib.h>
#include <wiiuse/wpad.h>
#include "include/WiiNetDbg.h"
#include "include/Menu.h"
#include "include/Map.h"


// le programme principal, fonction qui sera exécutée au lancement de l'application
int main(int argc, char **argv)
{
    // déclaration d'une variable pour fermer l'application
    bool done = false;

    // initialisation de la partie graphique via GRRLIB
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    #ifdef DEBUG // activation du débuggage uniquement si on est en target debug
    WiiNetDbg dbg(MYIP);
    #endif //DEBUG

	// on demande les informations sur les boutons, la caméra et les accéléromètres
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);

	vec3w_t accel;
	orient_t orien;
	expansion_t exp;
	ir_t ir;

    bool menu = true;
    Map carte = Map(1);

	// boucle qui continuera tant que l'application n'est pas arrêtée
	while(!done)
	{
		//récupération des informations des contrôleurs
		WPAD_ScanPads();
		//variable pressed remplit avec l'état des boutons du controleur 0
		u32 pressed = WPAD_ButtonsHeld(WPAD_CHAN_0);
		// On scane la manette et attribue les valeurs aux variables
		WPAD_ScanPads();
        WPAD_Accel(WPAD_CHAN_0, &accel);
	    WPAD_Orientation(WPAD_CHAN_0, &orien);
        WPAD_IR(WPAD_CHAN_0, &ir);
        WPAD_Expansion(WPAD_CHAN_0, &exp);

		// On sort de la boucle et donc on quitte le programme et on retourne au launcher si le bouton home est appuyé
		if ( pressed & WPAD_BUTTON_HOME ) {
            		if (menu) exit(0);
            		else menu = true;
		};

		if (menu) {
            menu = menu_index(ir, pressed);
		}
		else {
            carte.afficher_map(exp);
		}

		// On attend la prochaine trame à dessiner
		VIDEO_WaitVSync();
	}
	// valeur de retour, 0 = tout s'est bien passé
	return 0;
}
