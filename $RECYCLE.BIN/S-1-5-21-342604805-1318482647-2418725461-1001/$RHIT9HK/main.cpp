#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;

SDL_Window* gWindow = NULL;

//Starts up SDL and creates window
void init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

//Create character
SDL_Surface* gBox = NULL;

SDL_Event event;

void close()
{
	//Free loaded image
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		return 0;
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			return 0;
		}
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);
}

int main(int aggc,char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING    );
	gWindow = SDL_CreateWindow( "SDL Tutorial",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN );

				gScreenSurface = SDL_GetWindowSurface( gWindow );



            bool quit = false;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &event ) != 0 )
				{
					//User requests quit
					if( event.type == SDL_QUIT )
					{
						quit = true;
					}
//					else if(event.type == SDL_MOUSEMOTION){
//                        if(event.button.x>100)
//                            return 0;
////				SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );
//
//					}
				}
                gPNGSurface = loadSurface("box.png");
                ApplySurface(gPNGSurface, gScreenSurface, 0, 0);
                SDL_Surface* newS = loadSurface("1.png");
                ApplySurface(newS, gScreenSurface, 0, 0);



				SDL_UpdateWindowSurface( gWindow );
			}
	close();

	return 0;

}


