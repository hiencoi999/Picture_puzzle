#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <ctime>
#include <cstdlib>
#include "Texture.h"
#include "Window.h"

using namespace std;

const int SPACE = 50;
const int NUM_OF_ROWS = 4;
const int NUM_OF_COLS = 4;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gMenu = NULL;
SDL_Texture* loadingImage1 = NULL;
SDL_Texture* loadingImage2 = NULL;
SDL_Texture* win = NULL;
SDL_Texture* background = NULL;
//Đưa tên các ảnh vào 1 mảng string để load
const string Object[] = {"images//1.jpg", "images//2.jpg", "images//3.jpg", "images//4.jpg",
"images//5.jpg", "images//6.jpg", "images//7.jpg", "images//8.jpg", "images//9.jpg", "images//10.jpg",
"images//11.jpg", "images//12.jpg", "images//13.jpg", "images//14.jpg", "images//15.jpg", "images//16.jpg"};

struct Images
{
    SDL_Texture* gImage = NULL;
    int Count;
}grid[4][4];

//Hàm tạo game với các ảnh đã được đánh tráo
void CreateGame();

//Hàm thực hiện nội dung chính của game
void Game();


int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Event e;
    //Vòng lặp game
    if(init(gWindow, gRenderer) == NULL)
        return 0;
    else {
        //Khởi tạo các hình ảnh và tạo game
        CreateGame();

        while(1){
            while(SDL_PollEvent( &e ) != 0){
            if( e.type == SDL_QUIT )
                    {
                        return 0;
                    }
            }
            //Load menu
            SDL_RenderClear(gRenderer);
            SDL_RenderCopy(gRenderer, gMenu, NULL, NULL);
            SDL_RenderPresent(gRenderer);


            if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT)
                    Game();
            }

        }
//            SDL_RenderClear(gRenderer);
//            SDL_RenderCopy(gRenderer, gMenu,NULL,NULL);
//            SDL_RenderPresent(gRenderer);
//            SDL_Delay(5000);

    }
}

void CreateGame()
{
    int tmp = 0;
    //Load ảnh và tạo blendmode cho ảnh
    for(int i=0;i<NUM_OF_ROWS;i++){
        for(int j=0;j<NUM_OF_COLS;j++){
            grid[i][j].gImage = loadTexture(Object[tmp], gRenderer);
            grid[i][j].Count = tmp;// Lưu tmp của 16 hình ảnh vào mảng Count dùng để kiểm tra xem nếu người chơi win game
            SDL_SetTextureBlendMode(grid[i][j].gImage, SDL_BLENDMODE_BLEND);
            tmp++;
        }
    }
    //Tráo đổi ảnh ngẫu nhiên(đồng thời phải tráo đổi cả Count)
    for(int i=0;i<NUM_OF_ROWS;i++){
        for(int j=0;j<NUM_OF_COLS;j++){
                int temp1 = rand()%3; int temp2 = rand()%3;
            swap(grid[i][j].gImage, grid[temp1][temp2].gImage);
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
    //Load 2 ảnh menu để tạo hiệu ứng nhấp nháy
    loadingImage1 = loadTexture("images//loading1.png", gRenderer);
    SDL_SetTextureBlendMode(loadingImage1, SDL_BLENDMODE_BLEND);
    loadingImage2 = loadTexture("images//loading2.png", gRenderer);
    SDL_SetTextureBlendMode(loadingImage2, SDL_BLENDMODE_BLEND);

    //Load ảnh menu
    gMenu = loadTexture("images//menu.jpg", gRenderer);

    //Load background
    background = loadTexture("images//bg2.png", gRenderer);

    //Load ảnh khi win game
    win = loadTexture("images//win.png", gRenderer);
}

void Game()
{
    bool quit = false;

            int xMouse, yMouse, xMouse1, yMouse1, xMouse2, yMouse2, click = 0, num = 0, sum = 0, unknow = 1;
            bool isSwap = false, isTrue = false, isWin = false;
            int alpha = 255;


            while( !quit )
            {
                SDL_Event e;

                while( SDL_PollEvent( &e ) != 0 )
                {

                    if( e.type == SDL_QUIT )
                    {
                        quit = true;

                    }
                    if(isSwap){
                        for(int i=0;i<NUM_OF_ROWS;i++){
                            for(int j=0;j<NUM_OF_COLS;j++){
                                if(grid[i][j].Count != 4*i+j){
                                    isWin = false;
                                    break;
                                }
                                else isWin = true;
                            }
                        }
                    }
                        if(isWin == true){
                            SDL_RenderClear(gRenderer);
                            SDL_RenderCopy(gRenderer, win,NULL,NULL);
                            SDL_RenderPresent(gRenderer);
                            SDL_Delay(2000);
                            quit = true;
                        }




                    if(!isTrue){
                        for(int i=0;i<alpha/2;i++){
                            SDL_SetTextureAlphaMod(loadingImage1, i);
                            SDL_SetTextureAlphaMod(loadingImage2, i);
                            if(i%2==0)
                                SDL_RenderCopy(gRenderer, loadingImage1, NULL, NULL);
                            else
                                SDL_RenderCopy(gRenderer, loadingImage2, NULL, NULL);
                            SDL_RenderPresent(gRenderer);
                            SDL_Delay(100);
                        }
                        isTrue = true;
                    }


                    if(e.type == SDL_MOUSEMOTION){
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

                    if(e.type == SDL_MOUSEBUTTONDOWN ){
                            if(e.button.button == SDL_BUTTON_LEFT){
//                                if(!isSwap){
                                    if(e.button.x > SPACE && e.button.x < SCREEN_WIDTH-SPACE &&
                                       e.button.y > SPACE && e.button.y < SCREEN_HEIGHT-SPACE){
                                    click++;
                                    SDL_GetMouseState(&xMouse, &yMouse);
//                                    cout << xMouse << " " << yMouse << endl;
                                    }
//                                }
                                if(click == 1){
                                    xMouse1 = (xMouse-SPACE)/SIZE_1_GRID;
                                    yMouse1 = (yMouse-SPACE)/SIZE_1_GRID;
//                                    cout << xMouse1 << " " << yMouse1 << endl;
                                }
                                if(click == 2){
                                    xMouse2= (xMouse-SPACE)/SIZE_1_GRID;
                                    yMouse2=(yMouse-SPACE)/SIZE_1_GRID;
//                                    cout << xMouse2 << " " << yMouse2 << endl;

                                    swap(grid[yMouse1][xMouse1], grid[yMouse2][xMouse2]);
                                    click = 0;
                                    isSwap = true;
                                }
                            }

                    }

                    //Clear screen
                    SDL_RenderClear( gRenderer );

                    SDL_RenderCopy(gRenderer, background, NULL, NULL);
                    for(int i=0;i<NUM_OF_ROWS;i++){
                        for(int j=0;j<NUM_OF_COLS;j++){
                            ApplyTexture(gRenderer, grid[i][j].gImage, 0, 0, j*SIZE_1_GRID+SPACE, i*SIZE_1_GRID+SPACE);

                        }
                    }

                    //Cập nhật màn hình
                    SDL_RenderPresent( gRenderer );


                }
            }

    close(gWindow, gRenderer);
}
