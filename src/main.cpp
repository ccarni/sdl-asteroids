#include <iostream>
#include <SDL2/SDL.h>
#include "runner.h"

int main( int argc, char *argv[] ) {

    std::cout << "main running\n";

    Uint32 currentTime = 0;
    Uint32 lastTime = 0;
    float deltaTime = 0.0f;

    float FPS = 60;
    
    Runner* runner = new Runner();
    runner->Init();

    while(runner->GetRunning()) {
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; //milliseconds
        runner->Update(deltaTime);
        runner->Draw();
        lastTime = currentTime;

        SDL_Delay(1000.0f/FPS); // milliseconds
    }


    delete runner;

    std::cout << "exiting main\n";

    return 0;

}
