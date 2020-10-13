#ifndef FONCTIONS_FOR_SAVE_CHAR_H
#define FONCTIONS_FOR_SAVE_CHAR_H

SDL_Surface* ResizePictureForALetter(SDL_Surface *picture,int i_hg, 
        int i_bg, int j_hg, int j_hd);
SDL_Surface* Espace();
SDL_Surface* RetourALaLigne();
SDL_Surface* TexteFini();

int ItIsAWhiteSurface(SDL_Surface* picture);
int ThereIsABluePixel(SDL_Surface* picture, int ligne, int startColonne);
int FirstBlueLine(SDL_Surface* picture, int line);
int SizeOfSpaceBetweenLetters(int FisrtRedLigne, int SecondRedLigne);
int DoubleBlueLine(SDL_Surface* picture, int line, int column);

#endif
