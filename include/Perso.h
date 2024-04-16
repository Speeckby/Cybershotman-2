#ifndef PERSO_H
#define PERSO_H
#include "Caracteristique.h"


class Perso
{
    public:
        Perso(Caracteristique* caracteristiques);
        virtual ~Perso();

        Caracteristique* donnees;
        Equipement* inventaire;
    protected:

    private:
};

#endif // PERSO_H
