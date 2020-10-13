#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "display_picture.h"

#define w2 100
#define h2 100


// x = the line of pixel below the first red line
// y = the column of pixel at the right of the first blue line
// w = the length between the first blue line and the second blue line
// h = the length between the first red line and the second red line
SDL_Surface* ResizePictureForALetter(SDL_Surface *picture, int x,
        int y, int w, int h)
{   
    SDL_Surface* Resize = NULL; 

    Resize = SDL_CreateRGBSurface(0, w+1, h+1,32,0,0,0,0); // Create a surface
    
    if(Resize == NULL)
    {
        errx(1, "impossible creer la surface");   
    }
   
    SDL_Rect srcrect; //rect who 
    SDL_Rect dstrect;

    srcrect.x = y;
    srcrect.y = x;
    srcrect.w = w;
    srcrect.h = h;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 0;
    dstrect.h = 0;

    SDL_BlitSurface(picture, &srcrect, Resize, &dstrect);

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
   
    /*Uint32 pixel;
    pixel = SDL_MapRGB(Surface_Espace->format, 0, 255, 0);
    for(int i = 0; i < h2; i++)
        set_pixel(Surface_Espace, i, 10, pixel);*/
 

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
   
    /*Uint32 pixel;
    pixel = SDL_MapRGB(Surface_Espace->format, 0, 255, 0);
    for(int i = 0; i < h2; i++)
        set_pixel(Surface_Espace, i, 10, pixel);*/
 

    return Surface_Espace;
}

// Surface 3x3 pixel => The text is over
SDL_Surface* TexteFini()
{
    SDL_Surface* Surface_Espace = NULL;

    Surface_Espace = SDL_CreateRGBSurface(0, 3, 3, 32, 0, 0, 0, 0);
    
    if(Surface_Espace == NULL)
    {
        errx(1, "impossible creer la surface");   
    }

    SDL_FillRect(Surface_Espace, NULL, SDL_MapRGB(Surface_Espace->format, 255, 255, 255));
   
    /*Uint32 pixel;
    pixel = SDL_MapRGB(Surface_Espace->format, 0, 255, 0);
    for(int i = 0; i < h2; i++)
        set_pixel(Surface_Espace, i, 10, pixel);*/
 

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

int SizeOfSpaceBetweenLetters(SDL_Surface* picture)
{
    if(picture == NULL)
        return -1;

    return 3;
}

SDL_Surface **SaveAllLetters(SDL_Surface* picture)
{
    SDL_Surface **tableauDeSurface = malloc(sizeof(SDL_Surface)*1000);

    SDL_Surface *LettreSurface = NULL;
    int indexDuTableau = 0;

    int FirstRedLigne = 0; // The first red line
    int SecondRedLigne = 0; // The second red line

    //int RetourLigne = 1; // If = 0 there is a \n, 1 else

    Uint32 pixel;

    for(int i = 0; i < picture->h; i++)
    {
        Uint8 r, g, b;
        pixel = get_pixel(picture, 0, i);
        SDL_GetRGB(pixel, picture->format, &r, &g, &b);

        // Allow to frame a line thanks to red line created before
        if(r == 255 && g == 0 && b == 0) 
        {
            if(FirstRedLigne == 0) 
                FirstRedLigne = i+1;
            else
                SecondRedLigne = i-1;
        }

        
        printf("FirstRedLine : %d and SecondRedLine %d\n",FirstRedLigne,SecondRedLigne);

        if(FirstRedLigne != 0 && SecondRedLigne != 0 && (SecondRedLigne -
                FirstRedLigne) != 0)// If we are frame a letters' line and it is not 
                                //just an underscore line 
        {
            int RetourLigne = 1; // If = 0 there is a \n, 1 else

            int jProvisoire = FirstBlueLine(picture,FirstRedLigne);
            printf("jProvisoire : %d\n", jProvisoire);

            int StartColumn = jProvisoire; 

            if(jProvisoire != picture->w) // If there is at least one blue line
            {
                while(RetourLigne == 1)
                {

                    int jProvisoire2 = ThereIsABluePixel(picture,FirstRedLigne,StartColumn);
                    printf("jProvisoire 2 : %d\n", jProvisoire2);


                    if(jProvisoire2 == -1) // No more letter in the line
                    {
                        LettreSurface = RetourALaLigne();
                        tableauDeSurface[indexDuTableau] = LettreSurface;
                        indexDuTableau += 1;

                        RetourLigne = 0;
                    }
                    else //if(jProvisoire2 >= 3) // Space beetween two letter
                    {
                    
                        LettreSurface = ResizePictureForALetter(picture,
                            FirstRedLigne, StartColumn,jProvisoire2-StartColumn+1,
                            SecondRedLigne-FirstRedLigne+1);

                        int MaxSpaceBetweenLetters = SizeOfSpaceBetweenLetters(picture);
                        int res = ItIsAWhiteSurface(LettreSurface);

                        if(jProvisoire2 < MaxSpaceBetweenLetters && res == 0)
                        {
                            continue;
                        }
                        else
                        {
                            if(res == 0)
                                LettreSurface = Espace();

                            tableauDeSurface[indexDuTableau] = LettreSurface;
                            indexDuTableau += 1;
                        }
                    }

                    StartColumn = jProvisoire2 + 2;
                }
            }
                                        
            // resetting variables
            FirstRedLigne = 0;
            SecondRedLigne = 0;

            i-=1; // To test again the SecondRedLine because she can in the same time 
                //be the FirstRedLine of the next line
        }

        LettreSurface = RetourALaLigne();
        tableauDeSurface[indexDuTableau-1] = LettreSurface;
    }

    return tableauDeSurface;
}

