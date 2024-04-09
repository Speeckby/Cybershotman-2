#ifndef CARACTERISTIQUES_H
#define CARACTERISTIQUES_H


class Caracteristiques
{
    public:
        Caracteristiques(unsigned ax, unsigned ay, unsigned ahp, unsigned aradius, unsigned avit, GRRLIB_texImg* aimage);
        virtual ~Caracteristiques();

        x = ax;
        y = ay;
        hp = ahp;
        radius = araduis;
        vit = avit;
        image = aimage;

    protected:

    private:
};

#endif // CARACTERISTIQUES_H
