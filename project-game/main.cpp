#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <ctime>
#include <cstdlib>
#include "Texture.h"
#include "Window.h"

using namespace std;

const int SPACE = 50;
const int NUM_OF_ROWS = 5;
const int NUM_OF_COLS = 5;
const int MAX_OF_SWAP = 25;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gMenu = NULL;
SDL_Texture* loadingImage1 = NULL;
SDL_Texture* loadingImage2 = NULL;
SDL_Texture* background = NULL;
SDL_Texture* win = NULL;
SDL_Texture* lose = NULL;
SDL_Texture* MoveCount = NULL;

Mix_Music* gMusic = NULL;
Mix_Music* winsound = NULL;
Mix_Music* losesound = NULL;
Mix_Chunk* clicksound = NULL;
struct Images
{
    SDL_Texture* gImage = NULL;
    int x;
    int y;
    int Count;
}grid[NUM_OF_ROWS][NUM_OF_COLS];

//Hàm load game
void LoadGame();
//Hàm tạo game với các ảnh đã được đánh tráo
void CreateGame();

//Hàm thực hiện nội dung chính của game
void Game();


int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Event e1;
    //Vòng lặp game
    if(init(gWindow, gRenderer) == NULL)
        return 0;
    else {
        //Khởi tạo các hình ảnh và tạo game
        LoadGame();
        CreateGame();

        while(1){

            while(SDL_PollEvent( &e1 ) != 0){
            if( e1.type == SDL_QUIT )
                    {
                        return 0;
                    }
            }
            //Load menu
            SDL_RenderClear(gRenderer);
            SDL_RenderCopy(gRenderer, gMenu, NULL, NULL);
            SDL_RenderPresent(gRenderer);


            if(e1.type == SDL_MOUSEBUTTONDOWN){

                if(e1.button.button == SDL_BUTTON_LEFT)
                    Game();
            }
        }
    }
}

void LoadGame(){
    int tmp = 0;
    //Load ảnh và tạo blendmode cho ảnh
    for(int i=0;i<NUM_OF_ROWS;i++){
        for(int j=0;j<NUM_OF_COLS;j++){
            grid[i][j].gImage = loadTexture("images//game.jpg", gRenderer);
            grid[i][j].x = j*SIZE_1_GRID;
            grid[i][j].y = i*SIZE_1_GRID;
            grid[i][j].Count = tmp;// Lưu tmp của 16 hình ảnh vào mảng Count dùng để kiểm tra xem nếu người chơi win game
            SDL_SetTextureBlendMode(grid[i][j].gImage, SDL_BLENDMODE_BLEND);
            tmp++;
        }
    }
    //Load 2 ảnh menu để tạo hiệu ứng nhấp nháy
    loadingImage1 = loadTexture("images//load.png", gRenderer);
    SDL_SetTextureBlendMode(loadingImage1, SDL_BLENDMODE_BLEND);
    loadingImage2 = loadTexture("images//load2.png", gRenderer);
    SDL_SetTextureBlendMode(loadingImage2, SDL_BLENDMODE_BLEND);

    //Load ảnh menu
    gMenu = loadTexture("images//menu.jpg", gRenderer);

    //Load background
    background = loadTexture("images//bg2.png", gRenderer);

    //Load ảnh khi thắng game
    win = loadTexture("images//win.png", gRenderer);

    //Load ảnh khi thua
    lose = loadTexture("images//lose.png", gRenderer);

    //Thanh máu
    MoveCount = loadTexture("images//move_count.png", gRenderer);

    // Âm thanh
    gMusic = Mix_LoadMUS("music//Twerk.wav");
    if(gMusic == NULL) cout << "Could not open music" << endl;

    winsound = Mix_LoadMUS("music//winsound.mp3");
    if(winsound == NULL) cout << "Cound not open winsound" << endl;

    losesound = Mix_LoadMUS("music//losesound.mp3");
    if(losesound == NULL) cout << "Cound not open losesound" << endl;

    clicksound = Mix_LoadWAV("music//click.wav");
    if(clicksound == NULL) cout << "Could not open clicksound" << endl;
}

void CreateGame()
{
    //Tráo đổi ảnh ngẫu nhiên(đồng thời phải tráo đổi cả Count)
    for(int i=0;i<NUM_OF_ROWS;i++){
        for(int j=0;j<NUM_OF_COLS;j++){
                int temp1 = rand()%(NUM_OF_ROWS-1); int temp2 = rand()%(NUM_OF_COLS-1);
            swap(grid[i][j].x, grid[temp1][temp2].x);
            swap(grid[i][j].y, grid[temp1][temp2].y);
            swap(grid[i][j].Count, grid[temp1][temp2].Count);
        }
    }
    //Kiểm tra mảng Count
    for(int i=0;i<NUM_OF_ROWS;i++){
        for(int j=0;j<NUM_OF_COLS;j++){
            cout << grid[i][j].Count << " ";
        }
        cout << endl;
    }
}

void Game()
{
    bool once = false;

    bool quit = false, isSwap = false, Loading = false, Lose_PlayAgain = false, Win_PlayAgain = false;
    int xMouse, yMouse, xMouse1, yMouse1, xMouse2, yMouse2, click = 0;
    bool isWin;
    int alpha = 255;
    int move_count = MAX_OF_SWAP;

    while( !quit )
    {
        SDL_Event e;
        while( SDL_PollEvent( &e ) != 0 )
        {

            if( e.type == SDL_QUIT )
            {
                quit = true;

            }

            if(move_count == 0){
                    Lose_PlayAgain = true;
            }


            //Khởi tạo isWin = true kiểm tra nếu thắng
            isWin = true;

            if(isSwap){
                for(int i=0;i<NUM_OF_ROWS;i++){
                    for(int j=0;j<NUM_OF_COLS;j++){
                        if(grid[i][j].Count != NUM_OF_COLS*i+j){
                            isWin = false;
                        }
                    }
                }

                //Nếu win in ra ảnh You Win.
                if(isWin){
                    Win_PlayAgain = true;
                }

                isSwap = false;
            }
            // Tạo ảnh loading nhấp nháy
            if(!Loading){
                //Cho nhạc chờ chạy 1 lần
                Mix_PlayMusic(gMusic, 1);
                //Ảnh nhấp nháy sẽ hiện ra cho đến khi nhạc chờ hết
                for(int i=0;Mix_PlayingMusic() == 1;i++){
                    SDL_SetTextureAlphaMod(loadingImage1, i);
                    SDL_SetTextureAlphaMod(loadingImage2, i);
                    if(i%2==0)
                        SDL_RenderCopy(gRenderer, loadingImage1, NULL, NULL);
                    else
                        SDL_RenderCopy(gRenderer, loadingImage2, NULL, NULL);


                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(100);
                }

            }
            if(!Loading){
                //Tất cả grid.gImage đều load chung 1 ảnh nên chọn grid[0][0]
                SDL_RenderCopy(gRenderer, grid[0][0].gImage, NULL, NULL);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(3000);
                Loading = true;
            }
            // Kiểm tra vị trí của chuột đang ở đâu và tạo hiệu ứng mờ ảnh chuột đang trỏ đến
            if(e.type == SDL_MOUSEMOTION && !Lose_PlayAgain && !Win_PlayAgain){
                for(int i=0;i<NUM_OF_ROWS;i++){
                    for(int j=0;j<NUM_OF_COLS;j++){
                        if(e.button.y > i*SIZE_1_GRID+SPACE && e.button.y < (i+1)*SIZE_1_GRID+SPACE
                           && e.button.x > j*SIZE_1_GRID+SPACE && e.button.x < (j+1)*SIZE_1_GRID+SPACE){

                                SDL_SetTextureAlphaMod(grid[i][j].gImage, alpha/2);
                        }
                        else SDL_SetTextureAlphaMod(grid[i][j].gImage, alpha);
                    }
                }

            }

            if(e.type == SDL_MOUSEBUTTONDOWN && !Lose_PlayAgain && !Win_PlayAgain){
                    if(e.button.button == SDL_BUTTON_LEFT){
                            Mix_PlayChannel(-1, clicksound, 0);
                            //Lấy vị trí của chuột khi click
                            if(e.button.x > SPACE && e.button.x < SCREEN_WIDTH-SPACE &&
                               e.button.y > SPACE && e.button.y < SCREEN_HEIGHT-SPACE){
                            click++;
                            SDL_GetMouseState(&xMouse, &yMouse);
                            }

                        if(click == 1){
                            xMouse1 = (xMouse-SPACE)/SIZE_1_GRID;
                            yMouse1 = (yMouse-SPACE)/SIZE_1_GRID;
                            cout << xMouse1 << " " << yMouse1 << endl;
                        }
                        if(click == 2){
                            xMouse2= (xMouse-SPACE)/SIZE_1_GRID;
                            yMouse2=(yMouse-SPACE)/SIZE_1_GRID;
                            cout << xMouse2 << " " << yMouse2 << endl;
                            click = 0;
                            move_count--;
                            isSwap = true;
                        }
                    }

            }

            //Clear screen
            SDL_RenderClear( gRenderer );

            SDL_RenderCopy(gRenderer, background, NULL, NULL);
            for(int i=0;i<NUM_OF_ROWS;i++){
                for(int j=0;j<NUM_OF_COLS;j++){
                    ApplyTexture(gRenderer, grid[i][j].gImage, grid[i][j].x, grid[i][j].y, j*SIZE_1_GRID+SPACE, i*SIZE_1_GRID+SPACE);
                }
            }

            ApplyMoveCount(gRenderer, MoveCount, move_count*20);

            if(isSwap){
                swap(grid[yMouse1][xMouse1].x, grid[yMouse2][xMouse2].x);
                swap(grid[yMouse1][xMouse1].y, grid[yMouse2][xMouse2].y);
                swap(grid[yMouse1][xMouse1].Count, grid[yMouse2][xMouse2].Count);

            }

            if(Lose_PlayAgain == true){
                if(!once){
                    Mix_PlayMusic(losesound, 1);
                    once = true;
                }
                SDL_RenderCopy(gRenderer, lose, NULL, NULL);
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(e.button.button == SDL_BUTTON_LEFT){
                        if(e.button.x < 350 && e.button.y > 350)
                        {
                            Lose_PlayAgain = false;
                            once = false;
                            CreateGame();
                            move_count = MAX_OF_SWAP;
                        }
                        if(e.button.x >350 && e.button.y > 350){
                            quit = true;
                        }
                    }
                }

            }
            if(Win_PlayAgain == true){
                if(!once){
                    Mix_PlayMusic(winsound, 1);
                    once = true;
                }
                SDL_RenderCopy(gRenderer, win, NULL, NULL);
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(e.button.button == SDL_BUTTON_LEFT ){
                        if(e.button.x < 350 && e.button.y > 350)
                        {
                            Win_PlayAgain = false;
                            once = false;
                            CreateGame();
                            move_count = MAX_OF_SWAP;
                        }
                        if(e.button.x > 350 && e.button.y > 350){
                            quit = true;
                        }

                    }
                }

            }
            //Cập nhật màn hình
            SDL_RenderPresent( gRenderer );
        }
    }
    close(gWindow, gRenderer, gMusic, winsound, losesound, clicksound);
}
