#include "../include/Perso.h"

Perso::Perso(Caracteristiques* caracteristiques)
{
    donnees=caracteristiques;
}

Perso::est_mort()
{
    return donnees.hp <= 0;
}
Perso::desequiper("%d", bouton)
{
    delete inventaire[bouton];
}
Perso::tirer("%d", coord_x,"%d",coord_y,)
{
    delete inventaire[bouton];
}

Perso::~Perso()
{

}

