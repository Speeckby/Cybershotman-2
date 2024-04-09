#include "Monstre.h"
#include <stdlib.h>

Monstre::Monstre(int type, int x, int y)
{
    int x_monstre = rand() % 1480 - 740;
    if (x_monstre < -320 || x_monstre > 320) {
        int y_monstre = rand() % 820 - 410;
    } else {
        int y_monstre = rand() % 100 - 50;
        if (y_monstre < 0) {
            y_monstre -= 180;
        } else {
            y_monstre += 180;
        }
    }

    if (type == 0) {
        m_Carac = new Caracteristique(x + x_monstre, y + y_monstre, 100, 10, 2);
    }
}

Monstre::~Monstre()
{
    //dtor
}