#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "color_operations.h"
#include "image_operations.h"

SDL_Surface* SDL_Rotation(SDL_Surface* picture, float angle)
{
    SDL_Surface* res;
    int i;
    int j;
    Uint32 pixel;
    int mx, my;
    float d;
    int bx, by;
    float angle_radian;

/* détermine la valeur en radian de l'angle*/
    angle_radian = -angle * M_PI / 180.0;

/*
 * alloue la mémoire à l'espace de destination, attention,
 * la surface est de même taille
 */
    res = SDL_CreateRGBSurface(SDL_SWSURFACE, picture->w, picture->h, 
            picture->format->BitsPerPixel,
            picture->format->Rmask, picture->format->Gmask, 
            picture->format->Bmask, picture->format->Amask);

 /*on vérifie que la mémoire a été allouée*/
    if(res==NULL)
        return NULL;

/* pour simplifier les notations*/
    mx = picture->w/2;
    my = picture->h/2;

    for(j = 0; j < picture->h; j++)
        for(i = 0;i < picture->w; i++)
        {
/* on détermine la valeur de pixel qui correspond le mieux pour la position
 * i,j de la surface de destination */

/* on détermine la meilleure position sur la surface d'origine en appliquant
 * une matrice de rotation inverse
 */
             bx = (int) (cos(angle_radian) * (i-mx) + sin(angle_radian) * (j-my)) + mx;
             by = (int) (-sin(angle_radian) * (i-mx) + cos(angle_radian) * (j-my)) + my;
   /* on vérifie que l'on ne sort pas des bords*/
            if (bx>=0 && bx< picture->w && by>=0 && by< picture->h)
            {
                pixel = get_pixel(picture, bx, by);
                set_pixel(res, i, j, pixel);
            }
        }

    return res;
}
