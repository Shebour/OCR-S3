#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "display_picture.h"
#include "fonctions_for_save_char.h"

// x = the line of pixel below the first red line
// y = the column of pixel at the right of the first blue line
// w = the length between the first blue line and the second blue line
// h = the length between the first red line and the second red line
SDL_Surface* ResizePictureForALetter(SDL_Surface *picture, int x,
        int y, int w, int h)
{   
    SDL_Surface* Resize = NULL; 

    Resize = SDL_CreateRGBSurface(0, w, h,32,0,0,0,0); // Create a surface
    
   
    
    if(Resize == NULL)
    {
        errx(1, "impossible creer la surface");   
    }
   
    SDL_Rect srcrect; //rect who frame the letter that we need to cut 
    SDL_Rect dstrect; // position of the rect

    srcrect.x = y;
    srcrect.y = x;
    srcrect.w = w;
    srcrect.h = h;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 0;
    dstrect.h = 0;

    if(SDL_BlitSurface(picture, &srcrect, Resize, &dstrect) != 0)
        printf("SDL_BlitSurface failed: %s\n",SDL_GetError()); 

    return Resize;
}

// Surface 1x1 pixel => It is a space
SDL_Surface* Espace(void)
{
    SDL_Surface* Surface_Espace = NULL;

    Surface_Espace = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    
    if(Surface_Espace == NULL)
    {
        errx(1, "impossible creer la surface");   
    }

    SDL_FillRect(Surface_Espace, NULL, SDL_MapRGB(Surface_Espace->format, 255, 255, 255));

    return Surface_Espace;
}

// Surface 2x2 pixel => It is a \n
SDL_Surface* RetourALaLigne()
{
    SDL_Surface* Surface_Espace = NULL;

    Surface_Espace = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0);
    
    if(Surface_Espace == NULL)
    {
        errx(1, "impossible creer la surface");   
    }

    SDL_FillRect(Surface_Espace, NULL, SDL_MapRGB(Surface_Espace->format, 255, 255, 255));
   
    return Surface_Espace;
}


// Return 0 if the surface is white, 1 else
int ItIsAWhiteSurface(SDL_Surface* picture)
{
    Uint32 pixel;

    for(int i = 0; i < picture->h; i++)
    {
        for(int j = 0; j < picture->w; j++)
        {
            Uint8 r, g, b;
            pixel = get_pixel(picture, j, i);
            SDL_GetRGB(pixel, picture->format, &r, &g, &b);

            if(r == 0 && g == 0 && b == 0) // If the pixel is black
                return 1;
        }
    }
    return 0;
}

// Return j if there is in the line a blue pixel at the right of the startColonne, -1 else
int ThereIsABluePixel(SDL_Surface* picture, int line, int startColonne)
{
    Uint32 pixel;

    for(int j = startColonne; j < picture->w; j++)
    {
        Uint8 r, g, b;
        pixel = get_pixel(picture, j, line);
        SDL_GetRGB(pixel, picture->format, &r, &g, &b);

        if(r == 0 && g == 0 && b == 255) // If the pixel is blue
            return j-1;
    }
    return -1;
}

// Return j if there is a blue line, picture->w else
int FirstBlueLine(SDL_Surface* picture, int line)
{
    Uint32 pixel;

    for(int j = 0; j < picture->w; j++)
    {
        Uint8 r, g, b;
        pixel = get_pixel(picture, j, line);
        SDL_GetRGB(pixel, picture->format, &r, &g, &b);

        if(r == 0 && g == 0 && b == 255) // If the pixel is blue
            return j+1;
    }
    return picture->w;
}


// Probability of width of a space between 2 letters 
int SizeOfSpaceBetweenLetters(int FirstRedLine, int SecondRedLine)
{
    int result = SecondRedLine - FirstRedLine + 1;
    
    if(result >= 20)
        return result/4.5;
    else
        return result/7;
}

// If = 0 we are in a blue line, 1 else
int DoubleBlueLine(SDL_Surface* picture, int line, int column)
{
    Uint32 pixel;

    Uint8 r, g, b;
    pixel = get_pixel(picture, column, line);
    SDL_GetRGB(pixel, picture->format, &r, &g, &b);

    if(b == 255)
    {
        return 0;
    }
    return 1;
}

