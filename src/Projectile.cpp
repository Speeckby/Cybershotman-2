#include "../include/Projectile.h"
#include "../include/Caracteristiques.h"
#include <cmath>

Projectile::Projectile(int xperso, int yperso, int xviseur, int yviseur)
{
    Caracteristiques* m_cara;
    m_cara = new Caracteristique(xperso, yperso, 0, 20, 10);

    float alpha = atan(yviseur-yperso/xviseur-xperso);
    float dx = cos(alpha)*m_cara.m_vit;
    float dy = sin(alpha)*m_cara.m_vit;
}

Projectile::updatePos()
{
    m_cara.m_x = m_cara.m_x + dx;
    m_cara.m_y = m_cara.m_y + dy;
}

Projectile::~Projectile()
{
    //dtor
}
