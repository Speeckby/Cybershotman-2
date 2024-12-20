#include "../include/Monstre.h"
#include <stdlib.h>
#include <cmath>

Monstre::Monstre(int type, int x, int y, GRRLIB_texImg* img)
{
    int x_monstre = rand() % 940 - 740;
    int y_monstre = 0;
    if (x_monstre < -320 || x_monstre > 320) {
        y_monstre = rand() % 620 - 410;
    } else {
        y_monstre = rand() % 100 - 50;
        if (y_monstre < 0) {
            y_monstre -= 180;
        } else {
            y_monstre += 180;
        }
    }
    m_Carac = new Caracteristique(x + x_monstre, y + y_monstre, 100, 35, 3, img);
}

void Monstre::afficher_monstre(GRRLIB_texImg* img)
{
    GRRLIB_DrawTile(m_Carac->m_x, m_Carac->m_y, img, 0, 2, 2, 0xFFFFFFFF, 0);
}

void Monstre::deplacer_monstre(expansion_t exp, Perso* perso, int x_map, int y_map)
{
    float deltaX = perso->donnees->m_x - m_Carac->m_x;
    float deltaY = perso->donnees->m_y - m_Carac->m_y;
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance != 0) {
        float dx = (deltaX / distance) * m_Carac->m_vit;
        float dy = (deltaY / distance) * m_Carac->m_vit;

        m_Carac->m_x += dx - ((exp.nunchuk.js.pos.x-125)/30)*2;
        m_Carac->m_y += dy + ((exp.nunchuk.js.pos.y-125)/30)*2;
    }

    afficher_monstre(m_Carac->m_image);
}

bool Monstre::collision_monstre(Perso* perso)
{
    bool verif = false;
    if (m_Carac->m_y < perso->donnees->m_y+perso->donnees->m_radius && m_Carac->m_y > perso->donnees->m_y-perso->donnees->m_radius) {
        if (m_Carac->m_x < perso->donnees->m_x+perso->donnees->m_radius && m_Carac->m_x > perso->donnees->m_x-perso->donnees->m_radius) {
            verif = true;
        }
        }else{
        verif = false;}
    return verif;
}

void Monstre::collision_intermonstre(Monstre* autre_monstre) {
    float deltaX = autre_monstre->m_Carac->m_x - this->m_Carac->m_x;
    float deltaY = autre_monstre->m_Carac->m_y - this->m_Carac->m_y;
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    float minimum_distance = m_Carac->m_radius; // Adjust this value based on monster size

    if (distance < minimum_distance) {
        float overlap = minimum_distance - distance;
        float dx = (deltaX / distance) * overlap / 2.0f;
        float dy = (deltaY / distance) * overlap / 2.0f;

        this->m_Carac->m_x -= dx;
        this->m_Carac->m_y -= dy;
        autre_monstre->m_Carac->m_x += dx;
        autre_monstre->m_Carac->m_y += dy;
    }
}

Monstre::~Monstre() {
    delete m_Carac;
}
