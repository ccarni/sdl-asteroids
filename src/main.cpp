#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>


const int WIDTH = 800, HEIGHT = 800;

class Player {
    public:
        float xPos = 0, yPos = 0;
        float width = 10, height = 10;
        float rotAngle = 0;
        std::vector<float> tipPoint, backLeft, backRight;

        Player(float _width, float _height, float _xPos, float _yPos) {
            xPos = _xPos;
            yPos = _yPos;
            height = _height;
            width = _width;
        }

        void DrawPlayer(SDL_Renderer *renderer) {
            tipPoint = {xPos + (float)cos(rotAngle) * (width/2.0f), yPos - (float)sin(rotAngle) * (height/2.0f)};
            backLeft = {xPos - (float)sin(rotAngle + M_PI/4.0f) * (width/2.0f), yPos - (float)cos(rotAngle + M_PI/4.0f) * (height/2.0f)};
            backRight = {xPos + (float)sin(rotAngle - M_PI/4.0f) * (width/2.0f), yPos + (float)cos(rotAngle - M_PI/4.0f) * (height/2.0f)};

            SDL_RenderDrawPointF(renderer, xPos, yPos);
            SDL_RenderDrawLineF(renderer, tipPoint[0], tipPoint[1], backLeft[0], backLeft[1]);
            SDL_RenderDrawLineF(renderer, backLeft[0], backLeft[1], backRight[0], backRight[1]);
            SDL_RenderDrawLineF(renderer, backRight[0], backRight[1], tipPoint[0], tipPoint[1]);
        }

    private:
        

};


int main( int argc, char *argv[] ) {

    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );

    if ( window == nullptr ) {
        std::cout << "Error creating window: " << SDL_GetError( );
        return EXIT_FAILURE;
    }

    SDL_Event windowEvent;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player *pPlayer = new Player(900, 900, 400, 400);

    while (true) {
        if (SDL_PollEvent( &windowEvent )){
            if ( windowEvent.type == SDL_QUIT ){
                break;
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        pPlayer->DrawPlayer(renderer);

        SDL_RenderPresent(renderer);

        pPlayer->rotAngle += 0.0001f;
    }

    delete pPlayer;

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit( );

    return EXIT_SUCCESS;

}
