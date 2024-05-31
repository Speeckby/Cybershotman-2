#include "../include/Arme.h"

Arme::Arme(char nom, int id_arme, GRRLIB_texImg* arme_image)
{
    m_nom = nom;
    m_id = id_arme;
    m_armeimage = arme_image;
}

Arme::~Arme()
{
    //dtor
}
