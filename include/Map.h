#include <grrlib.h>
#include <wiiuse/wiiuse.h>
// src/Map.h
#ifndef MAP_H
#define MAP_H
 // Assurez-vous que cette ligne correspond à l'emplacement de GRRLIB.h dans votre projet

// Structure example pour expansion_t (modifiez selon vos besoins)
typedef struct {
    struct {
        struct {
            int x;
            int y;
        } js;
    } nunchuk;
} expansion_ts;

void afficher_map(expansion_t exp, GRRLIB_texImg* tuiles_carte, int x_map, int y_map);

#endif // MAP_H
