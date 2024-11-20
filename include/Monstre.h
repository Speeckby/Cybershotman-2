#ifndef MONSTRE_H
#define MONSTRE_H
#include "Perso.h"
#include "Caracteristique.h"

class Monstre
{
    public:
        Monstre(int type, int x, int y, GRRLIB_texImg* img);
        void afficher_monstre(GRRLIB_texImg* img);
        void deplacer_monstre(expansion_t exp,Perso* perso, int x_map, int y_map);
        bool collision_monstre(Perso* perso);
        void collision_intermonstre(Monstre* autre_monstre);
        virtual ~Monstre();


        Caracteristique * m_Carac;
        float x;
        float y;

    protected:

    private:
};

#endif // MONSTRE_H
