#include "../include/Projectile.h"
#include "../include/Caracteristique.h"
#include <cmath>

Projectile::Projectile(int xperso, int yperso, int xviseur, int yviseur)
{
    GRRLIB_texImg* img = GRRLIB_LoadTextureFromFile("sd:/Cybershotman2/Projectile_joueur.png");
    m_carac = new Caracteristique(xperso, yperso, 0, 20, 10, img);

    float alpha = atan(yviseur-yperso/xviseur-xperso);
    float dx = cos(alpha)*m_carac->m_vit;
    float dy = sin(alpha)*m_carac->m_vit;
}

void Projectile::updatePos()
{
    m_carac->m_x += dx;
    m_carac->m_y += dy;
}

Projectile::~Projectile()
{
    //dtor
}
