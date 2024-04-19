#include "src/getButtonStates.cpp"
#include <unordered_map>

std::unordered_map<std::string, bool> states = getButtonStates(pressed);

int perso_actuel = 0;

array personages[3] = {
    std::unordered_map<std::string, std::string> {
        "name": "perso1",
        "image": ""
    },
    std::unordered_map<std::string, std::string> {
        "name": "perso2",
        "image": ""
    },
    std::unordered_map<std::string, std::string> {
        "name": "perso3",
        "image": ""
    }
};

bool menu_colision(ir_t ir, int x1, int y1, int x2, int y2) {
    bool condition_x = ir.ax > x1 && ir.ay > y1;
    bool condition_y = ir.ax < x2 && ir.ay < y2;
    return condition_x && condition_y;
};

void afficher_perso() {
    string image_link = personages[perso_actuel]["image"];
    string name = personages[perso_actuel]["name"];
    GRRLIB_DrawImg(164,304,/*txtimg*/)
}

bool menu_play(ir_t ir) {
    if (!menu_colision(ir, 220, 240, 420, 300)) return false;
    if (states["A"]) return true;
};

void menu_leave(ir_t ir) {
    if (!menu_colision(ir, 320, 600, 360, 640)) return;
    if (states["A"]) exit(0);
};

void menu_droite(ir_t ir) {
    if (!menu_colision(ir, 420, 60, 480, 300)) return;
    if (perso_actuel == 2) perso_actuel = 0
    else perso_actuel = perso_actuel + 1;
};

void menu_gauche(ir_t ir) {
    if (!menu_colision(ir, 180, 60, 240, 300)) return;
    if (perso_actuel == 0) perso_actuel = 2
    else perso_actuel = perso_actuel - 1;
};

bool menu_index(ir_t ir) {

    GRRLIB_DrawImg(0,0,/*txtimg*/);
    afficher_perso();

    if (menu_play(ir)) return false;
    menu_leave(ir);
    menu_droite(ir);
    menu_gauche(ir);


    return true;
};
