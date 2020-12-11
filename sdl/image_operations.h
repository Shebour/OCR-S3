#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

//void rotation(SDL_Texture *texture, SDL_Renderer *renderer,
        //SDL_Rect srcR, SDL_Rect dstR, double angle);
int get_angle(SDL_Surface *picture);
SDL_Surface* rotation(SDL_Surface* origine, float angle);
#endif
