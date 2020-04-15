#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <vector>
using namespace std;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string Object[] = {"images//face.png", "images//youtube.png", "images//mail.png",
                        "images//cloud.png", "images//bird.png", "images//google.png"};

vector<vector<SDL_Surface* >> gPNG ;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);

SDL_Texture** loadTexture(SDL_Texture** Texture);
//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* background = NULL;

//Create character
SDL_Surface* gBox = NULL;

int main(int aggc,char* argv[])
{

    srand(time(0));
	//Start up SDL and create window
	if( !init() )
	{
		return 0;
	}
	else
	{
//		Load media
		if( !loadMedia() )
		{
			return 0;
		}
		else
		{
			// Creat 8x8 grid with 6 different object
			gPNG.resize(8);
			for(int i=0;i<8;i++)
            {
                gPNG[i].resize(8);
                for(int j=0;j<8;j++)
                {
                    int tmp = rand() % 6;
                    gPNG[i][j] = loadSurface(Object[tmp]);
                    ApplySurface(gPNG[i][j], gScreenSurface, (i+1)*53, (j+1)*53);
                }
            }
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT)
					{
						quit = true;
					}


				}


				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}
//
//	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "NGSINHHIEN",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN );

				gScreenSurface = SDL_GetWindowSurface( gWindow );


	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load background
	background = loadSurface( "images//box.png" );
	ApplySurface(background, gScreenSurface, 50, 50);
	if( background == NULL )
	{
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface( background );
	background = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		return 0;
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			return 0;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
		if (optimizedSurface != NULL)
        {
            Uint32 color_key = SDL_MapRGB(optimizedSurface->format, 0x00, 0x00, 0x00);
            SDL_SetColorKey(optimizedSurface, SDL_TRUE, color_key);
        }
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
