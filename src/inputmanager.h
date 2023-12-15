#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>

class InputManager {
    public:

        InputManager();

        bool GetQuit();
        int GetLRInput();
        int GetUDInput();

        void Update();


    private:
        int lrInput;
        int udInput;
        SDL_Event inputEvent;
        bool quit;
};

#endif