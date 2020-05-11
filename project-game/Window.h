#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
using namespace std;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

//Hàm tạo của sổ game
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
//Hàm xóa và thu hồi bộ nhớ
void close(SDL_Window* Window, SDL_Renderer* Renderer, Mix_Music* gMusic, Mix_Music* winsound, Mix_Music* losesound, Mix_Chunk* clicksound);

