#ifndef MONSTRE_H
#define MONSTRE_H


class Monstre
{
    public:
        Monstre(int type, int x, int y);
        virtual ~Monstre();

        Caracteristique GetCounter() { return m_Counter; }

        Caracteristique * m_Carac;

    protected:

    private:
};

#endif // MONSTRE_H
