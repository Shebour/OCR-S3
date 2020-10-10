#ifndef PIXEL_OPERATIONS_H
#define PIXEL_OPERATIONS_H

Uint32 get_pixel(SDL_Surface *picture, unsigned x, unsigned y);
void set_pixel(SDL_Surface *picture, unsigned x, unsigned y, Uint32 pixel);

#endif
