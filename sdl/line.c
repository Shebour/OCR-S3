#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "pixel_operations.h"
#include "trace.h"

void line_horizontal(SDL_Surface *picture)
{
    Uint32 pixel;
    int CheckIfFirstLigne = 0; // If = 0, line just above letters, if = 1, the one bellow

    for(int i = 0; i < picture->h; i++)
    {

        if(CheckIfFirstLigne == 0) // If it is a line above letters
        {
            for(int j = 0; j < picture->w; j++)
            {
                Uint8 r, g, b;
                pixel = get_pixel(picture, j, i);
                SDL_GetRGB(pixel, picture->format, &r, &g, &b);

                if(r == 0 && g == 0 && b == 0) // If the pixel is black
                {
                    if(i != 0)
                       trace_horizontal(picture,i-1);// See trace.c
                    CheckIfFirstLigne = 1; 
                    break;
                }
            }
        }

        if(CheckIfFirstLigne == 1) // If it is a line just below letters 
        {
            int ThereIsABlackPixel = 1; // If = 0, there is a black pixel in the
                                        // line, if = 1, there is not a black pixel
        
            for(int j = 0; j < picture->w; j++)
            {   
                Uint8 r, g, b;
                pixel = get_pixel(picture, j, i);
                SDL_GetRGB(pixel, picture->format, &r, &g, &b);

                if(r == 0 && g == 0 && b == 0) // If the pixel is black
                {
                    ThereIsABlackPixel = 0;
                    break;
                }
            }
        
            // If there is no black pixel in the line
            if(ThereIsABlackPixel == 1)
            {
                trace_horizontal(picture,i); // See trace.c
                CheckIfFirstLigne = 0; 
            }
        }
    }
}

void line_vertical(SDL_Surface * picture)
{
    Uint32 pixel;

    int FirstRedLigne = 0; // The first red line
    int SecondRedLigne = 0; // The second red line

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
                SecondRedLigne = i;
        }

        if(FirstRedLigne != 0 && SecondRedLigne != 0)// If we are frame a letters' line
        {
            int CheckIfFirstColonne = 0; // If = 0, the column just at the left of
                    // a letter, if = 1, the column just at the right of a letter
                                        
            for(int j = 0; j < picture->w; j++) 
            {

                if(CheckIfFirstColonne == 0) // If it is a line at the left of a letter
                {
                    for(int i2 = FirstRedLigne; i2 <= SecondRedLigne; i2++)
                    {
                        Uint8 r, g, b;
                        pixel = get_pixel(picture, j, i2);
                        SDL_GetRGB(pixel, picture->format, &r, &g, &b);

                        // Same condition in the line_horizontal function but here
                        // we are in vertical
                        if(r == 0 && g == 0 && b == 0)
                        {
                            if(j != 0)
                                trace_vertical(picture,j-1,FirstRedLigne,SecondRedLigne);
                            CheckIfFirstColonne = 1;
                            break;
                        }
                    }
                }

                if(CheckIfFirstColonne == 1) // If it is a line at the right of a letter
                {
                    int ThereIsABlackPixel = 1; // If = 0, there is a black pixel in the
                                        // line, if = 1, there is not a black pixel
       
                    for(int i2 = FirstRedLigne; i2 <= SecondRedLigne; i2++)
                    {   
                        Uint8 r, g, b;
                        pixel = get_pixel(picture, j, i2);
                        SDL_GetRGB(pixel, picture->format, &r, &g, &b);

                        if(r == 0 && g == 0 && b == 0)
                        {
                            ThereIsABlackPixel = 0;
                            break;
                        }
                    }

                    // If there is no black pixel in the column 
                    if(ThereIsABlackPixel == 1)
                    {
                        trace_vertical(picture,j,FirstRedLigne,SecondRedLigne);
                        CheckIfFirstColonne = 0; 
                    }
                }
            }

            // resetting variables
            FirstRedLigne = 0;
            SecondRedLigne = 0;

            i-=1; // To test again the SecondRedLine because she can in the same time 
                //be the FirstRedLine of the next line
        }
    }
}
