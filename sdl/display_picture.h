#ifndef DISPLAY_PICTURE_H
#define DISPLAY_PICTURE_H

void init();
SDL_Surface * load_picture(char *path);
void display(SDL_Surface * picture, int rot);
void wait_for_keypressed();
#endif
