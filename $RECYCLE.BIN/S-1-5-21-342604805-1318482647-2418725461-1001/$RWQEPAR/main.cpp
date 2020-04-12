//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <time.h>
//using namespace sf;
//
//int ts = 54; //tile size
//Vector2i offset(48,24);
//
//struct piece
//{ int x,y,col,row,kind,match,alpha;
//  piece(){match=0; alpha=255;}
//} grid[10][10];
//
//void swap(piece p1,piece p2)
//{
//  std::swap(p1.col,p2.col);
//  std::swap(p1.row,p2.row);
//
//  grid[p1.row][p1.col]=p1;
//  grid[p2.row][p2.col]=p2;
//}
//
//
//int main()
//{
//    srand(time(0));
//
//    RenderWindow app(VideoMode(740,480), "Match-3 Game!");
//    app.setFramerateLimit(60);
//
//    Texture t1,t2;
//    t1.loadFromFile("images/background.png");
//    t2.loadFromFile("bg2.png");
//
//    Sprite background(t1), gems(t2);
//
//    for (int i=1;i<=8;i++)
//     for (int j=1;j<=8;j++)
//      {
//          grid[i][j].kind=rand()%3;
//          grid[i][j].col=j;
//          grid[i][j].row=i;
//          grid[i][j].x = j*ts;
//          grid[i][j].y = i*ts;
//      }
//
//    int x0,y0,x,y; int click=0; Vector2i pos;
//    bool isSwap=false, isMoving=false;
//
//    while (app.isOpen())
//    {
//        Event e;
//        while (app.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//                app.close();
//
//            if (e.type == Event::MouseButtonPressed)
//                if (e.key.code == Mouse::Left)
//                {
//                   if (!isSwap && !isMoving) click++;
//                   pos = Mouse::getPosition(app)-offset;
//                }
//         }
//
//   // mouse click
//   if (click==1)
//    {
//      x0=pos.x/ts+1;
//      y0=pos.y/ts+1;
//    }
//   if (click==2)
//    {
//      x=pos.x/ts+1;
//      y=pos.y/ts+1;
//      if (abs(x-x0)+abs(y-y0)==1)
//        {swap(grid[y0][x0],grid[y][x]); isSwap=1; click=0;}
//      else click=1;
//    }
//
//   //Match finding
//   for(int i=1;i<=8;i++)
//   for(int j=1;j<=8;j++)
//   {
//    if (grid[i][j].kind==grid[i+1][j].kind)
//    if (grid[i][j].kind==grid[i-1][j].kind)
//     for(int n=-1;n<=1;n++) grid[i+n][j].match++;
//
//    if (grid[i][j].kind==grid[i][j+1].kind)
//    if (grid[i][j].kind==grid[i][j-1].kind)
//     for(int n=-1;n<=1;n++) grid[i][j+n].match++;
//   }
//
//   //Moving animation
//   isMoving=false;
//   for (int i=1;i<=8;i++)
//    for (int j=1;j<=8;j++)
//     {
//       piece &p = grid[i][j];
//       int dx,dy;
//       for(int n=0;n<4;n++)   // 4 - speed
//       {dx = p.x-p.col*ts;
//        dy = p.y-p.row*ts;
//        if (dx) p.x-=dx/abs(dx);
//        if (dy) p.y-=dy/abs(dy);}
//       if (dx||dy) isMoving=1;
//     }
//
//   //Deleting amimation
//   if (!isMoving)
//    for (int i=1;i<=8;i++)
//    for (int j=1;j<=8;j++)
//    if (grid[i][j].match) if (grid[i][j].alpha>10) {grid[i][j].alpha-=10; isMoving=true;}
//
//   //Get score
//   int score=0;
//   for (int i=1;i<=8;i++)
//    for (int j=1;j<=8;j++)
//      score+=grid[i][j].match;
//
//   //Second swap if no match
//   if (isSwap && !isMoving)
//      {if (!score) swap(grid[y0][x0],grid[y][x]); isSwap=0;}
//
//   //Update grid
//   if (!isMoving)
//    {
//      for(int i=8;i>0;i--)
//       for(int j=1;j<=8;j++)
//         if (grid[i][j].match)
//         for(int n=i;n>0;n--)
//            if (!grid[n][j].match) {swap(grid[n][j],grid[i][j]); break;};
//
//      for(int j=1;j<=8;j++)
//       for(int i=8,n=0;i>0;i--)
//         if (grid[i][j].match)
//           {
//            grid[i][j].kind = rand()%7;
//            grid[i][j].y = -ts*n++;
//            grid[i][j].match=0;
//            grid[i][j].alpha = 255;
//           }
//     }
//
//
//    //////draw///////
//    app.draw(background);
//
//    for (int i=1;i<=8;i++)
//     for (int j=1;j<=8;j++)
//      {
//        piece p = grid[i][j];
//        gems.setTextureRect( IntRect(p.kind*49,0,49,49));
//        gems.setColor(Color(255,255,255,p.alpha));
//        gems.setPosition(p.x,p.y);
//        gems.move(offset.x-ts,offset.y-ts);
//        app.draw(gems);
//      }
//
//     app.display();
//    }
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_image.h>

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

static const int width = 800;
static const int height = 600;

int main(int argc, char **argv)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture * image_texture = initialize_texture_from_file("bg2.png", renderer);
    int image_width, image_height;

    // Get texture width/height
    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;

    texture_destination.x = 100;
    texture_destination.y = 50;
    texture_destination.w = image_width;
    texture_destination.h = image_height;

    bool running = true;
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}


































//using namespace std;
//const int SCREEN_WIDTH = 680;
//const int SCREEN_HEIGHT = 380;
////The window we'll be rendering to
//SDL_Window* gWindow = NULL;
//
////Starts up SDL and creates window
//bool init();
//
////Loads media
//bool loadMedia();
//
////Frees media and shuts down SDL
//void close();
//
//
////Loads individual image
//SDL_Surface* loadSurface( std::string path );
//
////The surface contained by the window
//SDL_Surface* gScreenSurface = NULL;
//
////Current displayed PNG image
//SDL_Surface* gPNGSurface = NULL;
//
////Create character
//SDL_Surface* gBox = NULL;
//
//int main(int aggc,char* argv[])
//{
//	//Start up SDL and create window
//	if( !init() )
//	{
//		return 0;
//	}
//	else
//	{
//		//Load media
//		if( !loadMedia() )
//		{
//			return 0;
//		}
//		else
//		{
//			//Main loop flag
//			bool quit = false;
//
//			//Event handler
//			SDL_Event e;
//
//			//While application is running
//			while( !quit )
//			{
//				//Handle events on queue
//				while( SDL_PollEvent( &e ) != 0 )
//				{
//					//User requests quit
//					if( e.type == SDL_QUIT )
//					{
//						quit = true;
//					}
//				}
//
//				//Apply the PNG image
//				SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );
//
//				//Update the surface
//				SDL_UpdateWindowSurface( gWindow );
//			}
//		}
//	}
////
////	//Free resources and close SDL
//	close();
//
//	return 0;
//}
//
//bool init()
//{
//	//Initialization flag
//	bool success = true;
//
//	//Initialize SDL
//	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
//	{
//		success = false;
//	}
//	else
//	{
//		//Create window
//		gWindow = SDL_CreateWindow( "SDL Tutorial",
//                                    SDL_WINDOWPOS_CENTERED,
//                                    SDL_WINDOWPOS_CENTERED,
//                                    SCREEN_WIDTH,
//                                    SCREEN_HEIGHT,
//                                    SDL_WINDOW_SHOWN );
//		if( gWindow == NULL )
//		{
//			success = false;
//		}
//		else
//		{
//			//Initialize PNG loading
//			int imgFlags = IMG_INIT_PNG;
//			if( !( IMG_Init( imgFlags ) & imgFlags ) )
//			{
//				success = false;
//			}
//			else
//			{
//				//Get window surface
//				gScreenSurface = SDL_GetWindowSurface( gWindow );
//			}
//		}
//	}
//
//	return success;
//}
//
//bool loadMedia()
//{
//	//Loading success flag
//	bool success = true;
//
//	//Load PNG surface
//	gPNGSurface = loadSurface( "bg2.png" );
//	gBox = loadSurface("box.png");
//	if( gPNGSurface == NULL )
//	{
//		success = false;
//	}
//
//	return success;
//}
//
//void close()
//{
//	//Free loaded image
//	SDL_FreeSurface( gPNGSurface );
//	gPNGSurface = NULL;
//
//	//Destroy window
//	SDL_DestroyWindow( gWindow );
//	gWindow = NULL;
//
//	//Quit SDL subsystems
//	IMG_Quit();
//	SDL_Quit();
//}
//
//SDL_Surface* loadSurface( std::string path )
//{
//	//The final optimized image
//	SDL_Surface* optimizedSurface = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//	if( loadedSurface == NULL )
//	{
//		return 0;
//	}
//	else
//	{
//		//Convert surface to screen format
//		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
//		if( optimizedSurface == NULL )
//		{
//			return 0;
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface( loadedSurface );
//	}
//
//	return optimizedSurface;
//}
