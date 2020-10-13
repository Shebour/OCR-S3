#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <err.h>
#include "SDL2/SDL_image.h"
#include "pixel_operations.h"
#include "display_picture.h"
#include "fonctions_for_save_char.h"

SDL_Surface **SaveAllLetters(SDL_Surface* picture)
{
    SDL_Surface **tableauDeSurface = malloc(sizeof(SDL_Surface)*1000);

    SDL_Surface *LettreSurface = NULL;
    int indexDuTableau = 0;

    int FirstRedLigne = 0; // The first red line
    int SecondRedLigne = 0; // The second red line

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
                    else // Space beetween two letter
                    {
                    
                        LettreSurface = ResizePictureForALetter(picture,
                            FirstRedLigne, StartColumn,jProvisoire2-StartColumn+1,
                            SecondRedLigne-FirstRedLigne+1);

                        int MaxSpaceBetweenLetters = SizeOfSpaceBetweenLetters(picture);
                        int res = ItIsAWhiteSurface(LettreSurface);

                        // If the surface is white and is width is <= to MaxspaceBetween letter
                        if((jProvisoire2-StartColumn+1) <= MaxSpaceBetweenLetters && res == 0)
                        {
                            res = res + 1 - 1;// do nothing because it is a space between letter
                        }
                        else
                        {
                            if(res == 0)
                                LettreSurface = Espace();

                            tableauDeSurface[indexDuTableau] = LettreSurface;
                            indexDuTableau += 1;
                        }
                    }
                    
                    /*if(DoubleBlueLine(picture, FirstRedLigne ,jProvisoire2 + 2) == 0)
                        StartColumn = jProvisoire2 + 3;
                    else*/
                    StartColumn = jProvisoire2 + 2;

                }
            }
                                        
            // resetting variables
            FirstRedLigne = 0;
            SecondRedLigne = 0;

            i-=1; // To test again the SecondRedLine because she can in the same time 
                //be the FirstRedLine of the next line
        }

        LettreSurface = RetourALaLigne(); // after the last carater
        tableauDeSurface[indexDuTableau-1] = LettreSurface; // Change the last surface
                                        // for a surface with 3 pixel -> end of text
    }

    return tableauDeSurface;
}

