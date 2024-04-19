#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "include/WiiNetDbg.h"
#include <iostream>
#include <unordered_map>
#include "src/getButtonStates.cpp"
#include "src/menu.cpp"

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

void InitWii(void);

int main(int argc, char **argv) {

	InitWii();

	WPAD_SetDataFormat(WPAD_CHAN_0,WPAD_FMT_BTNS_ACC_IR);
	vec3w_t accel;
	orient_t orien;
	expansion_t exp;
	ir_t ir;

	WiiNetDbg dbg("192.168.1.236");

	bool menu = true;

	while(1)
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

	        // Boutons
	        std::unordered_map<std::string, bool> states = getButtonStates(pressed);

		if (pressed & WPAD_BUTTON_A)
           		 dbg.RPrint("Le bouton A vient d'etre appuye !");

		// On sort de la boucle et donc on quitte le programme et on retourne au launcher si le bouton home est appuyé
		if ( pressed & WPAD_BUTTON_HOME ) {
            		if (menu) exit(0);
            		else menu = true;
		};

		if (menu) {
            		menu = menu_index(ir);
		}
		else {
            		// jeu
		}

		// On attend la prochaine trame à dessiner
		VIDEO_WaitVSync();
	}
	// valeur de retour, 0 = tout s'est bien passé
	return 0;
}


void InitWii(void)
{
	// Initialisation du système vidéo
	VIDEO_Init();

	// initialisation des contrôleurs
	WPAD_Init();

	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	// Initialise the console, required for printf
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);

	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb);

	// Make the display visible
	VIDEO_SetBlack(FALSE);

	// Flush the video register changes to the hardware
	VIDEO_Flush();

	// Wait for Video setup to complete
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
}
