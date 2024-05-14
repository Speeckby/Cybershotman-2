#ifndef MAP_H
#define MAP_H
#include <grrlib.h>
#include <wiiuse/wiiuse.h>

class Map
{
    public:
        Map(int id_map);
        virtual ~Map();
        void afficher_map(expansion_t exp);
    protected:

    private:
        GRRLIB_texImg* m_tuiles_carte;
        double m_tab_map[36][36];
        int m_x_map;
        int m_y_map;
};

#endif // MAP_H
