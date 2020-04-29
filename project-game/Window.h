#include <SDL.h>
#include <SDL_image.h>
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;



//Hàm tạo của sổ game
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
//Hàm xóa và thu hồi bộ nhớ
void close(SDL_Window* Window, SDL_Renderer* Renderer);

