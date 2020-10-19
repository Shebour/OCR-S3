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

//Init the rendering management system
//Die with an error if not
void init(){
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Couldn't initialize SDL : %s;\n", SDL_GetError());
}

char wait_for_key_pressed(){    
    char key;
    if (scanf("%c", &key) == 'g')
        return key;
    else
        return 'a';    
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

    // Save all letters
    SDL_Surface **tab = SaveAllLetters(picture);
    for(int i = 0 ; i < 10; i++)
    {
        if(tab[i] == NULL)
            break;
        if(i < 10)
        {
            char NomLettre[16] = "Lettre/testi.bmp";
            NomLettre[11] = i;

            if(SDL_SaveBMP(tab[i],NomLettre) != 0)
                printf("SDL_SaveBMP failed: %s\n",SDL_GetError());
        }
        /*
        else if(10 <= i && i < 100)
        {
            char NomLettre[17] = "Lettre/testii.bmp";
            char j[2];
            sprintf(j,"%d",i);
            NomLettre[11] = j[0];
            NomLettre[12] = j[1];

            if(SDL_SaveBMP(tab[i],NomLettre) != 0)
                printf("SDL_SaveBMP failed: %s\n",SDL_GetError());
        }
        else if(100 <= i && i < 1000)
        {
            char NomLettre[18] = "Lettre/testiii.bmp";
            char j[3];
            sprintf(j,"%d",i);
            NomLettre[11] = j[0];
            NomLettre[12] = j[1];
            NomLettre[13] = j[2];

            if(SDL_SaveBMP(tab[i],NomLettre) != 0)
                printf("SDL_SaveBMP failed: %s\n",SDL_GetError());
        }
        else if(1000 <= i && i < 10000)
        {
            char NomLettre[19] = "Lettre/testiiii.bmp";
            char j[4];
            sprintf(j,"%d",i);
            NomLettre[11] = j[0];
            NomLettre[12] = j[1];
            NomLettre[13] = j[2];
            NomLettre[14] = j[3];

            if(SDL_SaveBMP(tab[i],NomLettre) != 0)
                printf("SDL_SaveBMP failed: %s\n",SDL_GetError());
        }*/
    }
    //printf("test : %d\n",(tab[0])->w);
    //for(int i = 0; i < 1000; i++)
        //free(tab[i]);
    //free(tab);

    
    //PourTester DONC ICI A ENLEVER APRES
    //picture = tab[24];


    //display it
    window = SDL_CreateWindow("OCR", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, picture->w, picture->h, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    //Free the memory used to display the picture
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(picture);
}

