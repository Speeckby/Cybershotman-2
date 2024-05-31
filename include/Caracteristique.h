#ifndef CARACTERISTIQUE_H
#define CARACTERISTIQUE_H
#include <grrlib.h>

class Caracteristique
{
    public:
        Caracteristique(int ax, int ay, int ahp, int aradius, int avit, GRRLIB_texImg* aimage);
        virtual ~Caracteristique();

        int GetX() { return m_x; }
        void SetX(int val) { m_x = val; }
        int GetY() { return m_y; }
        void SetY(int val) { m_y = val; }
        int GetHP() { return m_hp; }
        void SetHP(int val) { m_hp = val; }
        int GetRadius() { return m_radius; }
        void SetRadius(int val) { m_radius = val; }
        int GetVit() { return m_vit; }
        void SetVit(int val) { m_vit = val; }
        GRRLIB_texImg* GetImg() { return m_image; }
        void SetImg(GRRLIB_texImg* val) { m_image = val; }

        int m_x;
        int m_y;
        int m_hp;
        int m_radius;
        int m_vit;
        GRRLIB_texImg* m_image;

    protected:

    private:
};

#endif // CARACTERISTIQUE_H
