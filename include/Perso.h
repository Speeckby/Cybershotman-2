#ifndef PERSO_H
#define PERSO_H

#include "Caracteristique.h"
#include "Inventaire.h"
#include <wiiuse/wiiuse.h>
#include <set>
using namespace std;

class Perso
{
    public:
        Perso(Caracteristique* caracteristiques);
        void deplacer_perso(expansion_t exp);
        bool est_mort();
        void afficher_perso(int skin);
        int verif_y(int newCoordX, int newCoordY);
        int verif_x(int newCoordX, int newCoordY);
        int changement_sprite(expansion_t exp);

        virtual ~Perso();
        void reset();

        Caracteristique* donnees;
        Inventaire* inventaire;
    protected:

    private:
};

#endif // PERSO_H
