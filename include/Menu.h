#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <unordered_map>
#include <array>
#include <string>
#include <iostream>
#include <wiiuse/wiiuse.h>
#include <grrlib.h>
#include "../include/helper.h"

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        bool menu_colision(ir_t ir, int x1, int y1, int x2, int y2);
        void afficher_perso(const GRRLIB_texImg* img_menu[9]);
        bool menu_play(ir_t ir, std::unordered_map<std::string, bool> states);
        void menu_leave(ir_t ir, std::unordered_map<std::string, bool> states);
        void menu_droite(ir_t ir);
        void menu_gauche(ir_t ir);
        bool menu_index(ir_t ir, u32 held, u32 down, const GRRLIB_texImg* img_menu[9]);
        void afficher_menu(const GRRLIB_texImg** img_menu);
        void afficher_image(int coordX, int coordY, const GRRLIB_texImg* img);
    protected:

    private:
        int personnage;
};


#endif // MENU_H_INCLUDED
