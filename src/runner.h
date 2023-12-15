#ifndef RUNNER_H
#define RUNNER_H

#include "player.h"
#include "inputmanager.h"
#include <SDL2/SDL.h>

class Runner {
    public:
        bool running;

        bool GetRunning() const;

        Runner();
        ~Runner();

        void Init();
        void Update(float deltaTime);
        void Draw();
        void Cleanup();
    
    private:
        SDL_Window* window;
        float windowWidth, windowHeight;
        SDL_Event windowEvent;

        SDL_Renderer* renderer;

        Player* player;

        InputManager* inputManager;
        
};

#endif