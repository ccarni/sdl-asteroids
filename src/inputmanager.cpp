#include "inputmanager.h"
#include <SDL2/SDL.h>
#include <iostream>

InputManager::InputManager() {
    lrInput = 0;
    udInput = 0;
    quit = false;
}

void InputManager::Update() {
    lrInput = 0;
    udInput = 0;

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_A]) {
        lrInput--;
    }

    if (keystates[SDL_SCANCODE_D]) {
        lrInput++;
    }

    if (keystates[SDL_SCANCODE_W]) {
        udInput++;
    }

    if (keystates[SDL_SCANCODE_S]) {
        udInput--;
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