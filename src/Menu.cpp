#include "../include/Menu.h"

Menu::Menu()
{
    personnage = 0;
}

bool Menu::menu_colision(ir_t ir, int x1, int y1, int x2, int y2) {
    return ir.x > x1 && ir.y > y1 && ir.x < x2 && ir.y < y2;
}

void Menu::afficher_menu(const GRRLIB_texImg* img_menu[8]) {
    //afficher_image(0, 0, img_menu[7]);
    afficher_image(220, 0, img_menu[2]);
    afficher_image(320, 600, img_menu[3]);
    afficher_image(220, 240, img_menu[4]);
    afficher_image(180, 60, img_menu[5]);
    afficher_image(420, 60, img_menu[6]);
}

void Menu::afficher_image(int coordX, int coordY, const GRRLIB_texImg* img) {
    GRRLIB_DrawImg(coordX, coordY, img, 0, 1, 1, 0xFFFFFFFF);
}

void Menu::afficher_perso(const GRRLIB_texImg* img_menu[8]) {
    GRRLIB_DrawImg(164, 16, img_menu[personnage], 0, 10, 10, 0xFFFFFFFF);
}

bool Menu::menu_play(ir_t ir, std::unordered_map<std::string, bool> states) {
    if (!menu_colision(ir, 120, 140, 320, 240)) return false;
    return states["A"];
}

void Menu::menu_leave(ir_t ir, std::unordered_map<std::string, bool> states) {
    if (!menu_colision(ir, 320, 600, 360, 640)) return;
    if (states["A"]) exit(0);
}

void Menu::menu_droite(ir_t ir) {
    if (!menu_colision(ir, 500, 60, 540, 300)) return;
    if (personnage == 1) personnage = 0 ;
    else personnage ++;
}

void Menu::menu_gauche(ir_t ir) {
    if (!menu_colision(ir, 300, 60, 340, 300)) return;
    if (personnage == 0) personnage = 1 ;
    else personnage -= 1;
}

bool Menu::menu_index(ir_t ir, u32 held, u32 down, const GRRLIB_texImg* img_menu[8]) {
    std::unordered_map<std::string, bool> states = getButton(held, down);

    if (menu_play(ir, states)) return false;

    afficher_menu(img_menu);
    afficher_perso(img_menu);


    menu_leave(ir, states);
    if (states["A"]) {
        menu_droite(ir);
        menu_gauche(ir);
    }

    return true;
}

Menu::~Menu() {
    // dtor
}
