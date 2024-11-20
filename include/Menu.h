#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Perso.h"
#include <unordered_map>
#include <array>
#include <string>
#include <iostream>
#include <wiiuse/wiiuse.h>
#include <grrlib.h>
#include "helper.h"

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        bool menu_colision(ir_t ir, int x1, int y1, int x2, int y2);
        void afficher_perso(const GRRLIB_texImg* img_menu[8]);
        bool menu_play(ir_t ir, std::unordered_map<std::string, bool> states);
        void menu_leave(ir_t ir, std::unordered_map<std::string, bool> states);
        void menu_droite(ir_t ir);
        void menu_gauche(ir_t ir);
        bool menu_index(ir_t ir, u32 held, u32 down, const GRRLIB_texImg* img_menu[8], GRRLIB_texImg* img_perso[2], Perso * perso);
        void afficher_menu(const GRRLIB_texImg** img_menu);
        void afficher_image(int coordX, int coordY, const GRRLIB_texImg* img);

        int personnage;
    protected:

    private:
};


#endif // MENU_H_INCLUDED
