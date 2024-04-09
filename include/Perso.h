#ifndef PERSO_H
#define PERSO_H


class Perso
{
    public:
        Perso(Caracteristiques* caracteristiques);
        Caracteristiques* donnees;
        virtual ~Perso();

    protected:

    private:
};

#endif // PERSO_H
