#ifndef PERSO_H
#define PERSO_H
#include "Caracteristique.h"
#include "Inventaire.h"
#include <wiiuse/wiiuse.h>
#include "Projectile.h"


class Perso
{
    public:
        Perso(Caracteristique* caracteristiques);
        void deplacer_perso(expansion_t exp);
        bool est_mort();
        void afficher_perso();
        void init_perso();
        void tirer(set <Projectile> projectiles, ir_t ir);
        virtual ~Perso();

        Caracteristique* donnees;
        Inventaire* inventaire;
    protected:

    private:
};

#endif // PERSO_H
