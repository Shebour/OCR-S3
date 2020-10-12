#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"



/* Draw horizontal red line */
void trace_horizontal(SDL_Surface *picture, int i)
{
    Uint32 pixel;

    for(int j = 0; j < picture->w; j++)
    {
        pixel = SDL_MapRGB(picture->format, 255, 0, 0);
        set_pixel(picture, j, i, pixel);
    }
}

/* Draw vertical blue line */
void trace_vertical(SDL_Surface *picture, int j, int FirstLigne, int SecondLigne)
{
    Uint32 pixel;

    for(int i2 = FirstLigne; i2 < SecondLigne; i2++)
    {
        pixel = SDL_MapRGB(picture->format, 0, 0, 255);
        set_pixel(picture, j, i2, pixel);
    }

}
