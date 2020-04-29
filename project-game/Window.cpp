#include "Window.h"

bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer)
{
	//Initialization flag
	bool success = true;

	//Create window
        gWindow = SDL_CreateWindow( "PICTURE PUZZLE",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            success = false;
        }
        else
        {
            //Tạo renderer
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                success = false;
            }
            else
            {
                //Tạo màu cho renderer
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
        return success;
}

void close(SDL_Window* Window, SDL_Renderer* Renderer)
{
    //Free loaded image
//    SDL_DestroyTexture( gTexture );
//    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer( Renderer );
    SDL_DestroyWindow( Window );
    Window = NULL;
    Renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


