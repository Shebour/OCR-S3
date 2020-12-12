#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

int get_angle(SDL_Surface *picture);
SDL_Surface* rotation(SDL_Surface* origine, float angle);
#endif
