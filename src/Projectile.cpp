#include "../include/Projectile.h"
#include "../include/Caracteristique.h"
#include <cmath>

Projectile::Projectile(int xperso, int yperso, int xviseur, int yviseur, GRRLIB_texImg* img)
{
    m_carac = new Caracteristique(xperso, yperso, 0, 20, 10, img);
    float alpha = atan((yviseur-yperso)/(xviseur-xperso));
    dx = cos(alpha)*m_carac->m_vit;
    dy =  (alpha)*m_carac->m_vit;
}

void Projectile::updatePos()
{
    m_carac->m_x += dx;
    m_carac->m_y += dy;
}

bool Projectile::isHidden()
{
    if (m_carac->GetX() > 640) return true;
    if (m_carac->GetX() < 0) return true;
    if (m_carac->GetY() > 480) return true;
    if (m_carac->GetY() < 0) return true;

    return false;
}

void Projectile::display()
{
    GRRLIB_DrawTile(m_carac->GetX(),m_carac->GetY(),m_carac->m_image,0,1,1,0xFFFFFFFF, 0);
}

Projectile::~Projectile()
{
    delete m_carac;

}
