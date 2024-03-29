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
#include "image_operations.h"

void init(){
    //Init the rendering management system
    //Die with an error if not
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Couldn't initialize SDL : %s;\n", SDL_GetError());
}


void wait_for_keypressed()
{
    SDL_Event event;

    while(event.type != SDL_KEYDOWN)
        SDL_PollEvent(&event);

    while(event.type != SDL_KEYUP)
        SDL_PollEvent(&event);
}


SDL_Surface * load_picture(char *path){
    //Load the image (not especially a bitmap) from the path 
    //Die with an error if not
    SDL_Surface *picture;
    if (path != NULL)//check if path as a value
        picture = IMG_Load(path);
    else
        errx(1, "Path doesn't have a value");
    if (picture == NULL)//check if picture is initialized
        errx(1, "Couldn't initialize the picture : %s", SDL_GetError()); 
    return picture;
}


//display the picture
void display(SDL_Surface * picture, int rot){
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    //transform the picture
    grey_scale(picture);
    //black_white(picture);
    picture = b_w_threshold(picture);
    if (rot)
    {
        int angle = get_angle(picture);
        picture = rotation(picture, (-1)*angle);
    }
    reduce_noise(picture, 2);
    line_horizontal(picture);
    line_vertical(picture);

    
    //display it
    SDL_CreateWindowAndRenderer(picture->w, picture->h, 0, &window, &renderer);

    texture = SDL_CreateTextureFromSurface(renderer, picture);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    wait_for_keypressed();
    

    // Save all letters as a bitmap in the "Lettre" folder
    if (!rot)
        SaveAllLetters(picture);
    //Free the memory used to display the picture
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
}
