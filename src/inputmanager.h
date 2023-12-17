#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>

class InputManager {
    public:

        InputManager();

        bool GetQuit();
        int GetLRInput();
        int GetUDInput();
        bool GetSpace();

        void Update();


    private:
        bool quit;
        int lrInput;
        int udInput;
        bool spaceDown;
        SDL_Event inputEvent;
};

#endif