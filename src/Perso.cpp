#include "../include/Perso.h"
bool direction = true;

Perso::Perso(Caracteristique* caracteristiques)
{
    donnees = caracteristiques;
}

bool Perso::est_mort()
{
    return donnees->m_hp <= 0;
}
void Perso::deplacer_perso(expansion_t exp)
{
    int newCoordY = donnees->m_y + ((exp.nunchuk.js.pos.y - 125)/-20)*donnees->m_vit;
    int newCoordX = donnees->m_x - ((exp.nunchuk.js.pos.x - 127)/-20)*donnees->m_vit;

    donnees->m_x = verif_x(newCoordX, newCoordY);
    donnees->m_y = verif_y(newCoordX, newCoordY);

}

void Perso::afficher_perso(int skin)
{
    GRRLIB_DrawTile(donnees->m_x, donnees->m_y, donnees->m_image, 0,2,2,  0xFFFFFFFF, skin);
}
int Perso::verif_y(int newCoordX, int newCoordY) {
    if (newCoordY < 16) return 16; // Mur haut
    if (newCoordY > 357) return 357; // Mur bas
    if (newCoordX > 147 && newCoordX < 254) { // gestion cube centrale
        if (newCoordY > 124 && 136 > newCoordY) return 124;
        if (newCoordY < 218 && newCoordY > 198) return 218;
    }
    return newCoordY;
}
int Perso::verif_x(int newCoordX, int newCoordY) {
    if (newCoordX < 73) return 73; // Mur gauche
    if (newCoordX > 424) return 424; // Mur droite
    if (newCoordY > 124 && newCoordY < 208) { // gestion cube centrale
        if (newCoordX > 147 && 159 > newCoordX) return 147;
        if (newCoordX > 240 && 254 > newCoordX) return 254;
    };
    return donnees->m_x = newCoordX;
}
int Perso::changement_sprite(expansion_t exp)
{
    int pos_X = exp.nunchuk.js.pos.x;

    if (direction == true)
    {
        if (124<=pos_X && pos_X <= 130){ // Si neutre
            return 0;
        }
    }
    if (direction == false){
    if (124<=pos_X && pos_X <= 130){ // Si neutre
            return 1;
        }
    }
    if (pos_X<125){ // Si Gauche
        direction=false;
        return 8;
    }
    if (pos_X>130){ // Si Gauche
        direction=true;
        return 4;
    }
}
void Perso::reset() {
    donnees->m_x = 100;
    donnees->m_y = 200;
}
Perso::~Perso()
{

}
