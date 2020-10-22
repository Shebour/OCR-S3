#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"

Uint32 get_pixel(SDL_Surface *picture, unsigned x, unsigned y)
{
    //Check the format of each pixel and the pixel at position x, y
    int bpp = picture->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)picture->pixels + y * picture->pitch + x * bpp;

    //Check witch format it is and return the good value of the pixel
    switch (bpp)
    {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;
    }
}

void set_pixel(SDL_Surface *picture, unsigned x, unsigned y, Uint32 pixel){

    //Set the pixel "pixel" at the position x, y
    int bpp = picture->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)picture->pixels + y * picture->pitch
        + x * bpp;
    //Check the numbers of bytes using for the pixel to cast the pixel into the good format
    switch(bpp){
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else{
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

