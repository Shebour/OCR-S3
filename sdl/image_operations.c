#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "color_operations.h"
#include "image_operations.h"

void rotation(SDL_Texture *texture, 
        SDL_Renderer *renderer, SDL_Rect srcR,
        SDL_Rect dstR, double angle)
{
    SDL_Point center = {srcR.w / 2, srcR.h / 2};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, texture, &srcR, &dstR, angle, &center, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}

void surface_to_matrix(SDL_Surface *picture)
{
    Uint32 matrix[picture->w][picture->h];
    for (unsigned i = 0; i < picture->w; i++)
    {
        for (unsigned j = 0; j < picture->h; j++)
        {
            matrix[i][j] = get_pixel(picture, i, j);
            //printf("matrix[%u][%u] : %lu\n", i, j, matrix[i][j]);
        }
    }
}
