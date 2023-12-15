#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <vector>
#include "polygon.h"

class Player {
    public:
        void Init();

        Player();
        Player(float _width, float _height);
        Player(float x, float y, float _width, float _height);
        ~Player();

        void Draw(SDL_Renderer *renderer);
        void MovePlayer(float deltaTime, float turnInput, float forwardInput, float screenWidth, float screenHeight);
        void Fire();


    private:
        float width, height;
        std::vector<float> position, velocity, acceleration;

        float thrustAcceleration;
        float dragConstant;
        float maxSpeed;

        float rotAngle = 0;
        float turnSpeed;

        Polygon* polygon;
};

#endif