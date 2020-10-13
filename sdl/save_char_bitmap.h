#ifndef SAVE_CHAR_BITMAP_H
#define SAVE_CHAR_BITMAP_H


SDL_Surface* ResizePictureForALetter(SDL_Surface *picture,int i_hg, 
        int i_bg, int j_hg, int j_hd);
SDL_Surface* Espace();
SDL_Surface* RetourALaLigne();
SDL_Surface* TexteFini();

int ItIsAWhiteSurface(SDL_Surface* picture);
int ThereIsABluePixel(SDL_Surface* picture, int ligne, int startColonne);
int FirstBlueLine(SDL_Surface* picture, int line);
int SizeOfSpaceBetweenLetters(SDL_Surface* picture);


SDL_Surface** SaveAllLetters(SDL_Surface* picture);

//SDL_Surface ResizeTheLetter(SDL_Surface *LetterPicture);
//void saveCharBitmap(SDL_Surface *picture);

#endif
