#include "../include/Monstre.h"
#include <stdlib.h>

Monstre::Monstre(int type, int x, int y)
{
    int x_monstre = rand() % 1480 - 740;
    int y_monstre = 0;
    if (x_monstre < -320 || x_monstre > 320) {
        y_monstre = rand() % 820 - 410;
    } else {
        y_monstre = rand() % 100 - 50;
        if (y_monstre < 0) {
            y_monstre -= 180;
        } else {
            y_monstre += 180;
        }
    }

    if (type == 0) {
        GRRLIB_texImg* img = GRRLIB_LoadTextureFromFile("sd:/Cybershotman2/Monstre1.png");
        m_Carac = new Caracteristique(x + x_monstre, y + y_monstre, 100, 10, 2, img);
    }
}

Monstre::~Monstre()
{
    //dtor
}
