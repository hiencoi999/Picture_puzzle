//#include <SDL.h>
//
//
//
//
//
//
//int main(int argc, char **argv)
//{
//    int grid_cell_size = 50;
//    int grid_width = 10;
//    int grid_height = 10;
//
//    // + 1 so that the last grid lines fit in the screen.
//    int window_width = (grid_width * grid_cell_size)  ;
//    int window_height = (grid_height * grid_cell_size)  ;
//
//    // Place the grid cursor in the middle of the screen.
//    SDL_Rect grid_cursor = {
//        .x = (grid_width - 1) / 2 * grid_cell_size,
//        .y = (grid_height - 1) / 2 * grid_cell_size,
//        .w = grid_cell_size,
//        .h = grid_cell_size,
//    };
//
//    // The cursor ghost is a cursor that always shows in the cell below the
//    // mouse cursor.
//    SDL_Rect grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size,
//                                  grid_cell_size};
//
//    // Dark theme.
//    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
//    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
//    SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
//    SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White
//
//    // Light Theme.
//    // SDL_Color grid_background = {233, 233, 233, 255}; // Barely white
//    // SDL_Color grid_line_color = {200, 200, 200, 255}; // Very light grey
//    // SDL_Color grid_cursor_ghost_color = {200, 200, 200, 255};
//    // SDL_Color grid_cursor_color = {160, 160, 160, 255}; // Grey
//
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
//                     SDL_GetError());
//        return 0;
//    }
//
//    SDL_Window *window;
//    SDL_Renderer *renderer;
//    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,
//                                    &renderer) < 0) {
//        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
//                     "Create window and renderer: %s", SDL_GetError());
//        return 0;
//    }
//
//    SDL_SetWindowTitle(window, "SDL Grid");
//
//    SDL_bool quit = SDL_FALSE;
//    SDL_bool mouse_active = SDL_FALSE;
//    SDL_bool mouse_hover = SDL_FALSE;
//
//    while (!quit) {
//        SDL_Event event;
//        while (SDL_PollEvent(&event)) {
//            switch (event.type) {
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym) {
//                case SDLK_w:
//                case SDLK_UP:
//                    grid_cursor.y -= grid_cell_size;
//                    break;
//                case SDLK_s:
//                case SDLK_DOWN:
//                    grid_cursor.y += grid_cell_size;
//                    break;
//                case SDLK_a:
//                case SDLK_LEFT:
//                    grid_cursor.x -= grid_cell_size;
//                    break;
//                case SDLK_d:
//                case SDLK_RIGHT:
//                    grid_cursor.x += grid_cell_size;
//                    break;
//                }
//                break;
//            case SDL_MOUSEBUTTONDOWN:
//                grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
//                grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
//                break;
//            case SDL_MOUSEMOTION:
//                grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
//                grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;
//
//                if (!mouse_active)
//                    mouse_active = SDL_TRUE;
//                break;
//            case SDL_WINDOWEVENT:
//                if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
//                    mouse_hover = SDL_TRUE;
//                else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
//                    mouse_hover = SDL_FALSE;
//                break;
//            case SDL_QUIT:
//                quit = SDL_TRUE;
//                break;
//            }
//        }
//
//        // Draw grid background.
//        SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
//                               grid_background.b, grid_background.a);
//        SDL_RenderClear(renderer);
//
//        // Draw grid lines.
//        SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,
//                               grid_line_color.b, grid_line_color.a);
//
//        for (int x = 0; x < 1 + grid_width * grid_cell_size;
//             x += grid_cell_size) {
//            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
//        }
//
//        for (int y = 0; y < 1 + grid_height * grid_cell_size;
//             y += grid_cell_size) {
//            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
//        }
//
//        // Draw grid ghost cursor.
//        if (mouse_active && mouse_hover) {
//            SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r,
//                                   grid_cursor_ghost_color.g,
//                                   grid_cursor_ghost_color.b,
//                                   grid_cursor_ghost_color.a);
//            SDL_RenderFillRect(renderer, &grid_cursor_ghost);
//        }
//
//        // Draw grid cursor.
//        SDL_SetRenderDrawColor(renderer, grid_cursor_color.r,
//                               grid_cursor_color.g, grid_cursor_color.b,
//                               grid_cursor_color.a);
//        SDL_RenderFillRect(renderer, &grid_cursor);
////
//        SDL_RenderPresent(renderer);
//    }
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 480;
//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
LTexture gTextTexture;

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}
//Initialize PNG loading

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont( "16_true_type_fonts/lazy.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !gTextTexture.loadFromRenderedText( "The quick brown fox jumps over the lazy dog", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    return success;
}

void close()
{
    //Free loaded images
    gTextTexture.free();

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    //While application is running
            bool quit = false;
            SDL_Event e;
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
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render current frame
                gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
}
