#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "display_picture.h"

int main(int argc, char **argv){
    init();
    int p = argc;
    p++;
    SDL_Surface * picture;
    char *path = argv[1];
    picture = load_picture(path);
    display(picture);
    return 0;
}
