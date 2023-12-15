#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <vector>

class Player {
    public:
        void Init();

        Player();
        Player(float _width, float _height);
        Player(float x, float y, float _width, float _height);

        void DrawPlayer(SDL_Renderer *renderer);
        void MovePlayer(float deltaTime, float turnInput, float forwardInput, float screenWidth, float screenHeight);
        void Fire();


    private:
        float width = 10, height = 10;
        std::vector<float> position = {0.0f, 0.0f};
        std::vector<float> velocity = {0.0f, 0.0f};
        std::vector<float> acceleration = {0.0f, 0.0f};

        float thrustAcceleration;
        float dragConstant;
        float maxSpeed;

        float rotAngle = 0;
        float turnSpeed;

        std::vector<float> tipPoint, backLeft, backRight;
};

#endif