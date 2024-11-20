#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <wiiuse/wpad.h>
#include "Caracteristique.h"
#include "Perso.h"
#include "Monstre.h"

#include <cmath>

class Projectile
{
    public:
        Projectile(int xperso, int yperso, int xviseur, int yviseur, GRRLIB_texImg* img);
        void updatePos(expansion_t exp);
        void display();
        bool isHidden();
        bool collision(Monstre* monstre);
        virtual ~Projectile();

        Caracteristique* m_carac;
        float alpha;
        float dx;
        float dy;
        float x;
        float y;

    protected:

    private:

};

#endif // PROJECTILE_H
