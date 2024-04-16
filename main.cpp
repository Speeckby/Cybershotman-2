#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "include/WiiNetDbg.h"
#include <iostream>
#include <unordered_map>

#define WPAD_BUTTON_2							0x0001
#define WPAD_BUTTON_1							0x0002
#define WPAD_BUTTON_B							0x0004
#define WPAD_BUTTON_A							0x0008
#define WPAD_BUTTON_MINUS						0x0010
#define WPAD_BUTTON_HOME						0x0080
#define WPAD_BUTTON_LEFT						0x0100
#define WPAD_BUTTON_RIGHT						0x0200
#define WPAD_BUTTON_DOWN						0x0400
#define WPAD_BUTTON_UP						    0x0800
#define WPAD_BUTTON_PLUS						0x1000

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

// prototype (pré-déclaration) de la fonction InitWii()
void InitWii(void);

// le programme principal, fonction qui sera exécutée au lancement de l'application

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

std::unordered_map<std::string, bool> getButtonStates(int pressed) {
    std::unordered_map<std::string, bool> buttonStates;

    // Vérifie chaque bouton et définit la valeur correspondante dans le dictionnaire
    if (pressed & WPAD_BUTTON_HOME)
        buttonStates["Home"] = true;
    if (pressed & WPAD_BUTTON_A)
        buttonStates["A"] = true;
    if (pressed & WPAD_BUTTON_B)
        buttonStates["B"] = true;
    if (pressed & WPAD_BUTTON_1)
        buttonStates["1"] = true;
    if (pressed & WPAD_BUTTON_2)
        buttonStates["2"] = true;
    if (pressed & WPAD_BUTTON_MINUS)
        buttonStates["Minus"] = true;
    if (pressed & WPAD_BUTTON_PLUS)
        buttonStates["Plus"] = true;
    if (pressed & WPAD_BUTTON_UP)
        buttonStates["Up"] = true;
    if (pressed & WPAD_BUTTON_DOWN)
        buttonStates["Down"] = true;
    if (pressed & WPAD_BUTTON_LEFT)
        buttonStates["Left"] = true;
    if (pressed & WPAD_BUTTON_RIGHT)
        buttonStates["Right"] = true;
    if (pressed & WPAD_NUNCHUK_BUTTON_Z)
        buttonStates["Z"] = true;
    if (pressed & WPAD_NUNCHUK_BUTTON_C)
        buttonStates["C"] = true;

    return buttonStates;
}

int main(int argc, char **argv) {

	// lancement de la fonction InitWii, définie plus bas
	InitWii();

	// definition des variables de la manettes :
	WPAD_SetDataFormat(WPAD_CHAN_0,WPAD_FMT_BTNS_ACC);
	vec3w_t accel;
	orient_t orien;
	expansion_t exp;
	WPAD_SetDataFormat(WPAD_CHAN_0,WPAD_FMT_BTNS_ACC_IR);
	ir_t ir;
	// en mode texte, la console comprend les déplacements du curseur sous cette forme
	// on se déplace à la ligne 2, colonne 0
	printf("\x1b[2;0H");

	// boucle qui continuera tant que l'application n'est pas arrêtée

	WiiNetDbg dbg("192.168.1.236");
	while(1)
	{
		// On lance cette fonction pour récupérer les informations des contrôleurs
		WPAD_ScanPads();
		// Cette fonction nous remplit la variable pressed avec l'état des boutons du
		// controleur 0
		u32 pressed = WPAD_ButtonsHeld(WPAD_CHAN_0);
		// On scane la manette et attribue les valeurs aux variables
		WPAD_ScanPads();
        WPAD_Accel(WPAD_CHAN_0, &accel);		// le & permet de passer le pointeur vers la variable
        WPAD_Orientation(WPAD_CHAN_0, &orien); // pour que la fonction puisse la remplir
        WPAD_IR(WPAD_CHAN_0, &ir);
        WPAD_Expansion(WPAD_CHAN_0, &exp);
        // Boutons
        std::unordered_map<std::string, bool> states = getButtonStates(pressed);
        //printf(states);
        printf("\x1b[2;0H");
        for (auto iter = states.begin() ; iter != states.end(); ++iter)
        {
            printf("%s                   ",iter->first.c_str());
        }

		if (pressed & WPAD_BUTTON_A)
            dbg.RPrint("Le bouton A vient d'etre appuye !");

        #ifdef DEBUG
        WiiNetDbg dbg("192.168.0.75");
        #endif //DEBUG

        #ifdef DEBUG
        if (pressed & WPAD_BUTTON_A)
            dbg.RPrint("Le bouton A vient d'etre appuye !");
        #endif //DEBUG

		// On sort de la boucle et donc on quitte le programme
		// et on retourne au launcher si le bouton home est appuyé
		if ( pressed & WPAD_BUTTON_HOME )
			exit(0);

		// On attend la prochaine trame à dessiner
		VIDEO_WaitVSync();
	}
	// valeur de retour, 0 = tout s'est bien passé
	return 0;
}

