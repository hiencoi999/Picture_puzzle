#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <string>
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;

SDL_Window* window = NULL;
SDL_Surface* g_background = NULL;

SDL_Event g_event;

bool Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return false;
    window = SDL_CreateWindow("GAME",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_OPENGL);
    if(window == NULL)
        {
            return false;
        }
    return true;
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
        std::cout << "Unable to load image " << path.c_str() << "!" << std::endl;
    else{
        optimizedSurface = SDL_ConvertSurface(loadedSurface, g_background->format, 0);
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}
bool loadMedia()
{
    g_background = loadSurface("bg2.png");
    if(g_background == NULL)
    {
        return false;
    }
    return true;
}


int main(int argc, char* argv[])
{
    bool is_quit = false;
    if(Init() == NULL)
        std::cout << "Can not create the window!";

    if(!loadMedia()) std::cout << "Can not load media";
    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event))
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
        }
    }
    SDL_BlitSurface( g_background, NULL, g_background, NULL );
    SDL_UpdateWindowSurface( window );
    return 0;
}
