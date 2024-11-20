#include "../include/Projectile.h"

Projectile::Projectile(int xperso, int yperso, int xviseur, int yviseur, GRRLIB_texImg* img)
{
    m_carac = new Caracteristique(xperso, yperso, 0, 20, 4, img);
    alpha = atan2((yviseur-yperso),(xviseur-xperso));
    dx = cos(alpha) * m_carac->m_vit;
    dy = sin(alpha) * m_carac->m_vit;
}

void Projectile::updatePos(expansion_t exp)
{
    m_carac->m_x += dx - (exp.nunchuk.js.pos.x - 125) /30;
    m_carac->m_y += dy + (exp.nunchuk.js.pos.y - 125) /30;
}

bool Projectile::isHidden()
{
    if (m_carac->GetX() > 640) return true;
    if (m_carac->GetX() < 0) return true;
    if (m_carac->GetY() > 480) return true;
    if (m_carac->GetY() < 0) return true;


    return false;
}
bool Projectile::collision(Monstre* monstre) {
    float dx = m_carac->GetX() - monstre->m_Carac->m_x;
    float dy = m_carac->GetY() - monstre->m_Carac->m_y;
    float distance = sqrt(dx * dx + dy * dy);
    return distance < (monstre->m_Carac->m_radius + m_carac->m_radius);
}

void Projectile::display()
{
    GRRLIB_DrawTile(m_carac->GetX(),m_carac->GetY(),m_carac->m_image,alpha* (180.0 / 3.14),1,1,0xFFFFFFFF, 0);
}

Projectile::~Projectile()
{
    delete m_carac;

}
