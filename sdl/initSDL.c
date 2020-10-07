#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL_image.h>

void init(){
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Couldn't initialize SDL : %s;\n", SDL_GetError());
}

SDL_Surface *loadImage(char *path){
    SDL_Surface *image;
    image = SDL_LoadBMP(path);
    if (!image)
        errx(3, "Can't load %s : %s", path, IMG_GetError());
    return image;
}
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;
    }
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}


int main(){
    SDL_Window *window;
    SDL_Surface *image;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    init();
    window = SDL_CreateWindow("OCR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN);
    if (window == NULL){
        errx(1, "Could not initialize the window : %s", SDL_GetError());
    }
    image = loadImage("image.bmp");
    SDL_Color rgb;
    texture = SDL_CreateTextureFromSurface(renderer, image);
    for (int i = 0; i < image->w; i++){
        for (int j = 0; j < image->h; j++){
            Uint32 data = getpixel(image, i, j);
            SDL_GetRGB(data, image->format, &rgb.r, &rgb.g, &rgb.b);
            rgb.r = (int) rgb.r;
            rgb.g = (int) rgb.g;
            rgb.b = (int) rgb.b;
            printf("couleur i : %d j : %d RGB : %d / %d / %d\n", i, j, rgb.r, rgb.g, rgb.b);
        }
    }
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_Delay(10000);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    return 0;
}
