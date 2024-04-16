#ifndef MONSTRE_H
#define MONSTRE_H
#include "Caracteristique.h"

class Monstre
{
    public:
        Monstre(int type, int x, int y);
        virtual ~Monstre();

        Caracteristique * m_Carac;


    protected:

    private:
};

#endif // MONSTRE_H
