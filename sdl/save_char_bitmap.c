#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "display_picture.h"


void NumberOfLine(SDL_Surface *picture, int nbrLine);

struct Mot
{
    int lettres[50][50];
};

struct Ligne{
    struct Mot mots[10];
};

struct ElementsBitmap
{
    struct Ligne lignes[20];
};

void saveCharBitmap(SDL_Surface *picture)
{
    int nbrLine = 0;
    NumberOfLine(picture,nbrLine);

    int lettres[20][20];

    struct Mot mots[10] = 
    {
        lettres[][],
    };

    struct Ligne lignes[nbrLigne] = 
    {
        mots[],
    };

    struct ElementsBitmap Text = 
    {
        lignes[],
    };

}

void NumberOfLine(SDL_Surface *picture, int nbrLine)
{
    nbrLine = 1;
}


