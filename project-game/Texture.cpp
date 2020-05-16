#include "Texture.h"

SDL_Texture* loadTexture( std::string path , SDL_Renderer* &gRenderer)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        cout << "Unable to load image "<< path.c_str() << endl;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            cout << "Unable to create texture from " << path.c_str() << endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void ApplyTexture(SDL_Renderer* renderer, SDL_Texture* texture, int SIZE_1_GRID, int _x1, int _y1, int _x2, int _y2)
{
    SDL_Rect Src;
    SDL_Rect Dest;

    Src.x = _x1;
    Src.y = _y1;
    Src.w = SIZE_1_GRID;
    Src.h = SIZE_1_GRID;

    Dest.x = _x2;
    Dest.y = _y2;
    Dest.w = SIZE_1_GRID;
    Dest.h = SIZE_1_GRID;

    SDL_RenderCopy(renderer, texture, &Src, &Dest);
}

void ApplyMoveCount(SDL_Renderer* renderer, SDL_Texture* texture, int _w)
{
    SDL_Rect Src;
    SDL_Rect Dest;

    Src.x = 0;
    Src.y = 0;
    Src.w = 500;
    Src.h = 25;

    Dest.x = 155;
    Dest.y = 665;
    Dest.w = _w;
    Dest.h = 25;

    SDL_RenderCopy(renderer, texture, &Src, &Dest);
}


