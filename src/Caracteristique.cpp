#include "../include/Caracteristique.h"

Caracteristique::Caracteristique(int ax, int ay, int ahp, int aradius, int avit, GRRLIB_texImg* aimage)
{
    m_x = ax;
    m_y = ay;
    m_hp = ahp;
    m_radius = aradius;
    m_vit = avit;
    m_image = aimage;

}

Caracteristique::~Caracteristique()
{
    //dtor
}
