#include "runner.h"
#include "player.h"
#include "inputmanager.h"
#include <iostream>
#include <SDL2/SDL.h>

Runner::Runner() {
    running = true;
    windowWidth = 800;
    windowHeight = 800;
    window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    if ( window == nullptr ) {
        std::cout << "Error creating window: " << SDL_GetError( );
    }

    player = new Player(windowWidth/2.0f, windowHeight/2.0f, 20, 20);
    inputManager = new InputManager();

}

bool Runner::GetRunning() const {
    return running;
}

Runner::~Runner() {

    delete player;
    delete inputManager;

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit( );

}

void Runner::Init() {

}

void Runner::Update(float deltaTime) {
    // std::cout << "update called";
    if (SDL_PollEvent( &windowEvent )){
            if ( windowEvent.type == SDL_QUIT ){
                running = false;
                return;
            }
    }
    if (inputManager->GetQuit()) {
        running = false;
        return;
    }

    inputManager->Update();
    player->MovePlayer(deltaTime, inputManager->GetLRInput(), inputManager->GetUDInput(), windowWidth, windowHeight);
}

void Runner::Draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    player->DrawPlayer(renderer);

    SDL_RenderPresent(renderer);
}

void Runner::Cleanup() {
    
}
