#ifndef SAVE_CHAR_BITMAP_H
#define SAVE_CHAR_BITMAP_H

struct Mot
{
    size_t width;
    size_t height;
    int[][] *lettres[width][height];
}

struct Ligne{
    size_t size;
    struct Mot *mots[size];
}

struct ElementsBitmap
{
    size_t size;
    struct Ligne *lignes[size];
}

void saveCharBitmap(SDL_Surface *picture);

#endif
