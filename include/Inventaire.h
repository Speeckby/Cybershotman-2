#ifndef INVENTAIRE_H
#define INVENTAIRE_H
#include "Arme.h"


class Inventaire
{
    public:
        Inventaire(int taille, Arme arme);
        virtual ~Inventaire();

        int m_taille;
        Arme * m_arme;
    protected:

    private:
};

#endif // INVENTAIRE_H
