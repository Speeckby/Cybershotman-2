#ifndef ARME_H
#define ARME_H
#include <grrlib.h>


class Arme
{
    public:
        Arme(char nom, int id_arme, GRRLIB_texImg* arme_image);
        virtual ~Arme();
        char m_nom;
        int m_id;
        GRRLIB_texImg* m_armeimage;

    protected:

    private:

};

#endif // ARME_H
