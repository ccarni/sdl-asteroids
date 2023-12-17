#include "inputmanager.h"
#include <SDL2/SDL.h>
#include <iostream>

InputManager::InputManager() {
    quit = false;
    lrInput = 0;
    udInput = 0;
    spaceDown = false;
}

void InputManager::Update() {
    lrInput = 0;
    udInput = 0;
    spaceDown = false;

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_A] || keystates[SDL_SCANCODE_LEFT]) {
        lrInput--;
    }

    if (keystates[SDL_SCANCODE_D] || keystates[SDL_SCANCODE_RIGHT]) {
        lrInput++;
    }

    if (keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_UP]) {
        udInput++;
    }

    if (keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_DOWN]) {
        udInput--;
    }

    if (keystates[SDL_SCANCODE_SPACE]) {
        spaceDown = true;
    }

    while (SDL_PollEvent(&inputEvent)) {
        if (inputEvent.type == SDL_QUIT) {
            quit = true;
        }
    }

}

bool InputManager::GetQuit() {
    return quit;
}

int InputManager::GetLRInput() {
    // std::cout << "lrinput: " << lrInput << "\n";
    return lrInput;
}

int InputManager::GetUDInput() {
    return udInput; 
}

bool InputManager::GetSpace() {
    return spaceDown;
}