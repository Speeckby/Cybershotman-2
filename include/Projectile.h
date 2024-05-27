#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Caracteristique.h"

class Projectile
{
    public:
        Projectile(int xperso, int yperso, int xviseur, int yviseur, GRRLIB_texImg* img);
        void updatePos();
        void display();
        bool isHidden();
        virtual ~Projectile();

        Caracteristique* m_carac;
        int xviseur;
        int yviseur;
        float alpha;
        float dx;
        float dy;

    protected:

    private:

};

#endif // PROJECTILE_H
