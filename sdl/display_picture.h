#ifndef DISPLAY_PICTURE_H
#define DISPLAY_PICTURE_H

void init();
SDL_Surface * load_picture(char *path);
void display(SDL_Surface * picture);
//char wait_for_key_pressed();
#endif
