#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "display_picture.h"
#include "save_char_bitmap.h"

int main(int argc, char **argv){
    init();//init the lib sdl
    
    if (argc != 2)//two args to start, die with an error message if not
        errx(1, "Too few arguments");

    SDL_Surface * picture;
    
    char *path = argv[1];//get the path of the picture to display

    picture = load_picture(path);//load the picture thanks to the path
    
    display(picture);//display the picture

    SDL_FreeSurface(picture);//Free the memory used by the picture
    
    return 0;
}
