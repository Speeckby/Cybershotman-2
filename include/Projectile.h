#ifndef PROJECTILE_H
#define PROJECTILE_H


class Projectile
{
    public:
        Projectile(int xperso, int yperso, int xviseur, int yviseur);
        virtual ~Projectile();

        Caracteristiques* m_cara;
        int xviseur;
        int yviseur;
        float alpha;
        float dx;
        float dy;

    protected:

    private:

};

#endif // PROJECTILE_H
