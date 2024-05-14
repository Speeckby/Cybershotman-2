#include "../include/Perso.h"

Perso::Perso(Caracteristiques* caracteristiques)
{
    donnees=caracteristiques;
}

Perso::est_mort()
{
    return donnees.hp <= 0;
}
void Perso::deplacer_perso(expansion_t exp)
{
    donnees->m_x -= (exp.nunchuk.js.pos.x - 127)/20;
    donnees->m_y += (exp.nunchuk.js.pos.y - 125)/20;
}

void Perso::afficher_perso()
{
    GRRLIB_DrawTile(donnees->m_x, donnees->m_y, donnees->m_image, 0,1,1,  0xFFFFFFFF, 0);
}

Perso::~Perso()
{

}

