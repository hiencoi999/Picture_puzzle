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

         //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            cout << "SDL_mixer could not initialize! SDL_mixer Error: "<< Mix_GetError() ;
            success = false;
        }
        return success;
}

void close(SDL_Window* Window, SDL_Renderer* Renderer, Mix_Music* gMusic, Mix_Chunk* clicksound)
{
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    Mix_FreeChunk(clicksound);
    clicksound = NULL;
    //Destroy window
    SDL_DestroyRenderer( Renderer );
    SDL_DestroyWindow( Window );
    Window = NULL;
    Renderer = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

