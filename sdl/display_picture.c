#include "SDL2/SDL.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "color_operations.h"
#include "line.h"
#include "save_char_bitmap.h"
#include "display_picture.h"
//Init the rendering management system
//Die with an error if not
void init(){
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Couldn't initialize SDL : %s;\n", SDL_GetError());
}


void wait_for_keypressed()
{
    SDL_Event event;

    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

//Load the image (not especially a bitmap)
//Die with an error if not
SDL_Surface * load_picture(char *path){ 
    SDL_Surface *picture;
    if (path != NULL)//check if path as a value
        picture = IMG_Load(path);
    else
        errx(1, "no path");
    if (picture == NULL)//check if picture is initialized
        errx(1, "Could not open the picture : %s", SDL_GetError()); 
    return picture;
}


//display the picture
void display(SDL_Surface * picture){
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    //transform the picture
    grey_scale(picture);
    black_white(picture);
    line_horizontal(picture);
    line_vertical(picture);

    //display it
    window = SDL_CreateWindow("OCR", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, picture->w, picture->h, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    wait_for_keypressed();

    // Save all letters as a bitmap in the "Lettre" folder
    SDL_Surface **tab = SaveAllLetters(picture);

    for(int i = 0 ; i < 10000; i++)
    {
        if(tab[i] == NULL)
            break;
        
        char s[30];
        snprintf(s, 30, "Lettres/LettreNumero_%d.bmp", i);

        if(SDL_SaveBMP(tab[i], s) != 0)
            printf("Couldn't save BMP: %s\n",SDL_GetError());
    }

    int i = 0;
    while(tab[i] != NULL){
        free(tab[i]);
        i++;
    }
    //Free the memory used to display the picture
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
}
