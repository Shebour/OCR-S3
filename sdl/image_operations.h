#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

void rotation(SDL_Texture *texture, SDL_Renderer *renderer,
        SDL_Rect srcR, SDL_Rect dstR, double angle);
void surface_to_matrix(SDL_Surface *picture);
#endif
