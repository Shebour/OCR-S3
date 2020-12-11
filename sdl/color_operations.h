#ifndef COLOR_OPERATIONS_H
#define COLOR_OPERATIONS_H

void grey_scale(SDL_Surface *picture);
void black_white(SDL_Surface *picture);
Uint32 mediane(SDL_Surface *picture, int i, int j, int n);
void reduce_noise(SDL_Surface *picture, int n);
#endif
