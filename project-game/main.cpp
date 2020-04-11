#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

const string Object[] = {"images//Blue.png", "images//Red.png", "images//Yellow.png", "images//Purple.png",
                        "images//Orange.png", "images//Green.png"};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void ApplyTexture(SDL_Renderer* renderer, SDL_Texture* texture, int _x1, int _y1, int _x2, int _y2);

void ExChange(int arr[8][8], int temp[8][8] );
//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

SDL_Texture* EMPTY = NULL;
vector <vector<SDL_Texture* > > gPNG;



SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
bool init()
{
	//Initialization flag
	bool success = true;

	//Create window
        gWindow = SDL_CreateWindow( "CANDY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    success = false;
                }
            }
        }
        return success;
}
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load PNG texture
    gTexture = loadTexture( "box.png" );
    if( gTexture == NULL )
    {
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[])
{
    srand(time(0));
//Main loop flag
    if(init() == NULL)
        return 0;
    else {
        if(loadMedia()){
            bool quit = false;

            //Event handler
            SDL_Event e;

            int arr[8][8];
			gPNG.resize(8);
			for(int i=0;i<8;i++)
            {
                gPNG[i].resize(8);
                for(int j=0;j<8;j++)
                {
                    int tmp = rand() % 6;
                    arr[i][j] = tmp;
                    gPNG[i][j] = loadTexture(Object[tmp]);

                }
            }
        int temp[8][8];
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                temp[i][j] = arr[i][j];
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        bool isRunning;

        do{

            do {
                isRunning = false;


                // Duyet theo hang ngang
                for(int i=0;i<8;i++){
                    for(int j=0;j<6;j++){
                        if(arr[i][j] == arr[i][j+1] && arr[i][j] == arr[i][j+2]) {
                            temp[i][j] = 10;
                            temp[i][j+1] = 10;
                            if(arr[i][j+2] == arr[i][j+3]){
                                temp[i][j+2] = 10;
                                if(arr[i][j+3] == arr[i][j+4])
                                    temp[i][j+3] = 10; temp[i][j+4] = 10;
                            }
                            else
                                temp[i][j+2] = 10;
                        }
                    }
                }

                // Duyet theo hang doc
                for(int i=0;i<8;i++){
                    for(int j=0;j<6;j++){
                        if(arr[i][j] == arr[i+1][j] && arr[i][j] == arr[i+2][j]) {
                            temp[i][j] = 10;
                            temp[i+1][j] = 10;
                            if(arr[i+2][j] == arr[i+3][j]){
                                temp[i+2][j] = 10;
                                if(arr[i+3][j] == arr[i+4][j])
                                    temp[i+3][j] = 10; temp[i+4][j] = 10;
                            }
                            else
                                temp[i+2][j] = 10;
                        }
                    }
                }

                // Xoa object va tao object moi
                for(int k=0;k<8;k++){
                    for(int i=0;i<8;i++){
                        for(int j=0;j<8;j++){
                            if(temp[0][j] == 10 ) {
                                temp[0][j] = rand() % 6;
                                gPNG[0][j] = loadTexture(Object[temp[0][j]]);
                                isRunning = true;
                            }
                            if(temp[i][j] == 10) {
                                swap(temp[i][j], temp[i - 1][j]);
                                gPNG[i][j] = EMPTY;
                                swap(gPNG[i][j], gPNG[i-1][j]);

                                isRunning = true;
                            }
                        }
                    }
                }

                for(int i=0;i<8;i++){
                    for(int j=0;j<8;j++){
                        arr[i][j] = temp[i][j];
                    }
                }
                for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    cout << arr[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            }while(isRunning);

        }while(isRunning);



                //While application is running
                while( !quit )
                {
                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }



                        if(e.type == SDL_MOUSEBUTTONDOWN )
                            if(e.button.button == SDL_BUTTON_LEFT && e.button.x < 50 && e.button.y < 50){

                                swap(gPNG[0][0], EMPTY);

                                this_thread::sleep_for(chrono::milliseconds(1000));

                            if(e.button.button == SDL_BUTTON_LEFT)
                                swap(gPNG[0][0], gPNG[0][1]);
                                 this_thread::sleep_for(chrono::milliseconds(1000));
                            }

                    }


                    //Clear screen
                    SDL_RenderClear( gRenderer );

                    //Render texture to screen
                    SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

                    for(int i=0;i<8;i++){
                        for(int j=0;j<8;j++){
                            ApplyTexture(gRenderer, gPNG[i][j], 0, 0, j*50, i*50);
                        }
                    }

                    //Update screen
                    SDL_RenderPresent( gRenderer );

                }
            }
    }
    close();
}
void ApplyTexture(SDL_Renderer* renderer, SDL_Texture* texture, int _x1, int _y1, int _x2, int _y2)
{
    SDL_Rect Src;
    SDL_Rect Dest;

    Src.x = _x1;
    Src.y = _y1;
    Src.w = 50;
    Src.h = 50;

    Dest.x = _x2;
    Dest.y = _y2;
    Dest.w = 50;
    Dest.h = 50;

    SDL_RenderCopy(renderer, texture, &Src, &Dest);
}


