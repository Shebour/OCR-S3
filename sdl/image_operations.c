#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "color_operations.h"
#include "image_operations.h"
#include "display_picture.h"
#define PI 3.14159265


void angle_min_y (SDL_Surface* picture, int* tab) 
{
    Uint32 pixel;

    Uint8 r,g,b;
    int height = picture -> h;
    int width = picture -> w;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel = get_pixel(picture, j, i);
            SDL_GetRGB(pixel, picture ->format, &r, &g, &b);
            if (r != 255)
            {
                tab[0] = j;
                tab[1] = i;
            }
        }
    }
}

void angle_max_x (SDL_Surface* picture, int* tab) 
{
    Uint32 pixel;

    Uint8 r,g,b;
    int height = picture -> h;
    int width = picture -> w;
    for(int j = width - 1; j >  0; j--)
    {
        for(int i = 0; i < height; i++)
        {
            pixel = get_pixel(picture, j, i);
            SDL_GetRGB(pixel, picture ->format, &r, &g, &b);
            if (r != 255)
            {
                tab[0] = j;
                tab[1] = i;
            }
        }
    }
}

int get_angle(SDL_Surface *picture)
{
    int res[2];
    angle_min_y(picture, res);
    int Xa = res[0];
    int Ya = res[1];
    angle_max_x(picture,res);
    int Xb = res[0];
    int Yb = res[1];
    double a_maxx = Yb - Ya;
    double miny_a = Xb - Xa;
    double miny_maxx = sqrt(miny_a*miny_a + a_maxx*a_maxx);
    double val = 180.0 / PI;
    int angle = asin(a_maxx/miny_maxx) * val;
    return angle;
}

SDL_Surface* rotation(SDL_Surface* origine, float angle)
{
    SDL_Surface* destination;
    int i;
    int j;
    Uint32 couleur;
    int mx, my, mxdest, mydest;
    int bx, by;
    float angle_radian;
    float tcos;
    float tsin;
    double largeurdest;
    double hauteurdest;
 
    /* détermine la valeur en radian de l'angle*/
    angle_radian = -angle * M_PI / 180.0;
 
    /*pour éviter pleins d'appel, on stocke les valeurs*/
    tcos = cos(angle_radian);
    tsin = sin(angle_radian);
 
    /*calcul de la taille de l'image de destination*/
    largeurdest=   ceil(origine->w * fabs(tcos) + origine->h * fabs(tsin)),
    hauteurdest=   ceil( origine->w * fabs(tsin) + origine->h * fabs(tcos)),
 
 
    /* 
    * alloue la mémoire à l'espace de destination, attention, 
    * la surface est de même taille
    */
    destination = SDL_CreateRGBSurface(SDL_SWSURFACE, largeurdest, hauteurdest, origine->format->BitsPerPixel,
			origine->format->Rmask, origine->format->Gmask, origine->format->Bmask, origine->format->Amask);
    for (size_t i = 0; i < destination->w; i++)
    {
        for (size_t j = 0; j < destination->h; j++)
        {
            Uint8 r, g, b;
            r = g = b = 255;
            Uint32 pixel = SDL_MapRGB(destination->format, r, g, b);  
            set_pixel(destination, i, j, pixel);
        }
    }
 
    /*on vérifie que la mémoire a été allouée*/
    if(destination==NULL)
        return NULL;
 
    /*calcul du centre des images*/
    mxdest = destination->w/2.;
    mydest = destination->h/2.;
    mx = origine->w/2.;
    my = origine->h/2.;
 
    for(j=0;j<destination->h;j++)
        for(i=0;i<destination->w;i++)
    {
        /* on détermine la valeur de pixel qui correspond le mieux pour la position
        * i,j de la surface de destination */
 
        /* on détermine la meilleure position sur la surface d'origine en appliquant
        * une matrice de rotation inverse
        */
 
        bx = (ceil (tcos * (i-mxdest) + tsin * (j-mydest) + mx));
        by = (ceil (-tsin * (i-mxdest) + tcos * (j-mydest) + my));
        /* on vérifie que l'on ne sort pas des bords*/
        if (bx>=0 && bx< origine->w && by>=0 && by< origine->h)
        {
            couleur = get_pixel(origine, bx, by);
            set_pixel(destination, i, j, couleur);
        }
    }  
 
    return destination;
}
