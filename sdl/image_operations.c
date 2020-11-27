#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "color_operations.h"
#include "image_operations.h"
#include "SDL2/SDL2_rotozoom.h"

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
