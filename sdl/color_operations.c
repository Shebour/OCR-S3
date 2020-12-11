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

int partition(Uint32 arr[], int begin, int end)
{
   Uint32 pivot = arr[end];
   int i = begin - 1;
   for (int j = begin; j < end; j++)
   {
        if (arr[j] < pivot)
        {
            i++;
            Uint32 temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
   }
   Uint32 temp = arr[i+1];
   arr[i+1] = arr[end];
   arr[end] = temp;
   return i+1;
}

void quicksort(Uint32 arr[], int begin, int end)
{
    if (begin < end)
    {
        int pi = partition(arr, begin, end);

        quicksort(arr, begin, pi -1);
        quicksort(arr, pi + 1, end);
    }
}



Uint32 mediane(SDL_Surface * picture, int i, int j, int n){
    //Set the size of the surface to cover
    int initial_h = i;
    int initial_w = j;
    int final_h = i + n;
    int final_w = j + n;
    //Get the number of pixels to use the median filter
    int nb_pixel = n * n;
    Uint32 pixel;
    Uint8 r, g, b;
    Uint32 r_list[nb_pixel];
    Uint32 g_list[nb_pixel]; 
    Uint32 b_list[nb_pixel];
    int index = 0;
    //Go through the picture
    for (i = initial_h; i < final_h; i++){
        for (j = initial_w; j < final_w; j++){
            pixel = get_pixel(picture, i , j);
            SDL_GetRGB(pixel, picture->format, &r, &g, &b);
            //Sum each colors value of each pixels in the area
            r_list[index] = r;
            g_list[index] = g;
            b_list[index] = b;
            index++;
        }
    }
    //Get the new color
    quicksort(r_list, 0, nb_pixel);
    quicksort(g_list, 0, nb_pixel);
    quicksort(b_list, 0, nb_pixel);
    if (nb_pixel % 2 == 0)
        pixel = SDL_MapRGB(picture->format, (int)(r_list[nb_pixel / 2]), (int) (g_list[nb_pixel / 2]), (int)(b_list[nb_pixel / 2]));
    else
        pixel = SDL_MapRGB(picture->format, (int) (r_list[nb_pixel / 2 + 1]), (int) (g_list[nb_pixel / 2 + 1]), (int)(b_list[nb_pixel / 2 + 1]));
    return pixel;
}

void reduce_noise(SDL_Surface *picture, int n){

    for (int i = 0; i < picture->w; i++){
        for (int j = 0; j < picture->h; j++){
            //Get the current pixel
            Uint32 pixel = get_pixel(picture, i, j);
            //Get the new color
            pixel = mediane(picture, i, j, n);
            //Set the new color in the pixel
            set_pixel(picture, i, j, pixel);
        }
    }
}
