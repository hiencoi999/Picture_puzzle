#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <string>
using namespace std;

const int SIZE_1_GRID = 120;

//Hàm đưa ảnh lên màn hình
void ApplyTexture(SDL_Renderer* renderer, SDL_Texture* texture, int _x1, int _y1, int _x2, int _y2);

void ApplyMoveCount(SDL_Renderer* renderer, SDL_Texture* texture, int _w);

SDL_Texture* loadTexture( std::string path , SDL_Renderer* &gRenderer);


