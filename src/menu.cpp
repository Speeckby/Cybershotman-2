#include "../include/Menu.h"

int perso_actuel = 0;

std::array<std::unordered_map<std::string, const char*>, 3> personages = {
    std::unordered_map<std::string, const char*> {
        {"name", "perso1"},
        {"image", "sd:/Cybershotman2/perso1.png"}
    },
    std::unordered_map<std::string, const char*> {
        {"name", "perso2"},
        {"image", "sd:/Cybershotman2/perso2.png"}
    },
    std::unordered_map<std::string, const char*> {
        {"name", "perso3"},
        {"image", "sd:/Cybershotman2/perso3.png"}
    }
};

bool menu_colision(ir_t ir, int x1, int y1, int x2, int y2) {
    bool condition_x = ir.ax > x1 && ir.ay > y1;
    bool condition_y = ir.ax < x2 && ir.ay < y2;
    return condition_x && condition_y;
};

void afficher_perso() {
    const char* image_link = personages[perso_actuel]["image"];
    std::string name = personages[perso_actuel]["name"];
    GRRLIB_texImg* image = GRRLIB_LoadTextureFromFile(image_link);
    GRRLIB_DrawImg(164,304,image, 0,2,2, 0xFFFFFFFF);
}

bool menu_play(ir_t ir, std::unordered_map<std::string, bool> states) {
    if (!menu_colision(ir, 220, 240, 420, 300)) return false;
    if (states["A"]) return true;
    return false;
};

void menu_leave(ir_t ir, std::unordered_map<std::string, bool> states) {
    if (!menu_colision(ir, 320, 600, 360, 640)) return;
    if (states["A"]) exit(0);
};

void menu_droite(ir_t ir) {
    if (!menu_colision(ir, 420, 60, 480, 300)) return;
    if (perso_actuel == 2) perso_actuel = 0;
    else perso_actuel = perso_actuel + 1;
};

void menu_gauche(ir_t ir) {
    if (!menu_colision(ir, 180, 60, 240, 300)) return;
    if (perso_actuel == 0) perso_actuel = 2;
    else perso_actuel = perso_actuel - 1;
};

bool menu_index(ir_t ir, u32 pressed) {

    std::unordered_map<std::string, bool> states = getButton(pressed);
    // Afficher menu  :
    /*GRRLIB_DrawImg(0,0,);*/
    afficher_perso();

    if (menu_play(ir, states)) return false;
    menu_leave(ir, states);
    menu_droite(ir);
    menu_gauche(ir);


    return true;
};
