#ifndef RUNNER_H
#define RUNNER_H

#include "player.h"
#include "asteroid.h"
#include "inputmanager.h"
#include <SDL2/SDL.h>
#include <vector>

class Runner {
    public:
        bool running;

        bool GetRunning() ;

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

        std::vector<Asteroid*> asteroids;
        
};

#endif