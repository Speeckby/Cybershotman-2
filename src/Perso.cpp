#include "../include/Perso.h"

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
    donnees->m_x -= ((exp.nunchuk.js.pos.x - 127)/-20)*donnees->m_vit;
    donnees->m_y += ((exp.nunchuk.js.pos.y - 125)/-20)*donnees->m_vit;
}

void Perso::afficher_perso()
{
    GRRLIB_DrawTile(donnees->m_x, donnees->m_y, donnees->m_image, 0,2,2,  0xFFFFFFFF, 0);
}
void Perso::init_perso()
{
    GRRLIB_texImg* tuiles_perso = GRRLIB_LoadTextureFromFile("sd:/survivor/player/purple_sprite.png");
    GRRLIB_InitTileSet(tuiles_perso, 32,32,0);

}

void Perso::tirer(set <Projectile> projectiles, ir_t ir)
{
    projectiles.insert(new Projectile(donnees->GetX(),donnees->GetY(), ir.x, ir.y))
}

Perso::~Perso()
{

}

