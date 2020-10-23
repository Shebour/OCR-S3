#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "color_operations.h"


void grey_scale(SDL_Surface *picture){
    //Transform the picture in a grey scale
    Uint32 pixel;
    for (int i = 0; i < picture->w; i++){
        for (int j = 0; j < picture->h; j++){
            Uint8 r, g, b;
            //Get the pixel of the picture thanks to his coordinates
            pixel = get_pixel(picture, i, j);
            //Get the color in RGB of the pixel
            SDL_GetRGB(pixel, picture->format, &r, &g, &b);
            Uint32 average = 0.3 * r + 0.59 * g + 0.11 * b;
            r = b = g = average;
            //Set the new color in the pixel
            pixel = SDL_MapRGB(picture->format, r, g, b);
            //Replace the old pixel by this new one
            set_pixel(picture, i, j, pixel);
        }
    }
}


void black_white(SDL_Surface *picture){
    //Transform the picture in black and white
    //Same procedure as grey_scale
    Uint32 pixel;
    for (int i = 0; i < picture->w; i++){
        for (int j = 0; j < picture->h; j++){
            Uint8 r, g, b;
            pixel = get_pixel(picture, i, j);
            SDL_GetRGB(pixel, picture->format, &r, &g, &b);
            if (r > 255 / 2)
                r = 255;
            else
                r = 0;
            if (g > 255 / 2)
                g = 255;
            else
                g = 0;
            if (b > 255 / 2)
                b = 255;
            else
                b = 0;
            pixel = SDL_MapRGB(picture->format, r, g, b);
            set_pixel(picture, i, j, pixel);
        }
    } 
}

Uint32 average(SDL_Surface * picture, int i, int j, int n){
    //Set the size of the surface to cover
    int initial_h = i;
    int initial_w = j;
    int final_h = i + n;
    int final_w = j + n;
    //Get the number of pixels to use the median filter
    int nb_pixel = n * n;
    Uint32 pixel;
    Uint8 r, g, b;
    Uint32 r_sum = 0, g_sum = 0, b_sum = 0;
    //Go through the picture
    for (i = initial_h; i < final_h; i++){
        for (j = initial_w; j < final_w; j++){
            pixel = get_pixel(picture, i , j);
            SDL_GetRGB(pixel, picture->format, &r, &g, &b);
            //Sum each colors value of each pixels in the area
            r_sum += r;
            g_sum += g;
            b_sum += b;
        }
    }
    //Get the new color
    pixel = SDL_MapRGB(picture->format, (int)(r / nb_pixel), (int) (g_sum / nb_pixel), (int)(b_sum / nb_pixel));
    return pixel;
}

void reduce_noise(SDL_Surface *picture){
    Uint32 av;
    for (int i = 0; i < picture->w; i++){
        for (int j = 0; j < picture->h; j++){
            //Get the current pixel
            Uint32 pixel = get_pixel(picture, i, j);
            //Get the new color
            pixel = average(picture, i, j, 1);
            //Set the new color in the pixel
            set_pixel(picture, i, j, pixel);
        }
    }
}
