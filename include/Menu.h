#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <unordered_map>
#include <array>
#include <string>
#include <iostream>
#include <wiiuse/wiiuse.h>
#include <grrlib.h>
#include "../include/helper.h"

bool menu_colision(ir_t ir, int x1, int y1, int x2, int y2);
void afficher_perso();
bool menu_play(ir_t ir, std::unordered_map<std::string, bool> states);
void menu_leave(ir_t ir, std::unordered_map<std::string, bool> states);
void menu_droite(ir_t ir);
void menu_gauche(ir_t ir);
bool menu_index(ir_t ir, u32 pressed);


#endif // MENU_H_INCLUDED
