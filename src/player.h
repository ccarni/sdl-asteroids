#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <vector>
#include "polygon.h"
#include "bullet.h"

class Player {
    public:
        void Init();

        Player();
        Player(float _width, float _height);
        Player(float x, float y, float _width, float _height);
        ~Player();

        void Update(float deltaTime, float turnInput, float forwardInput, float screenWidth, float screenHeight);
        void Draw(SDL_Renderer *renderer);
        
        void Fire(float fireSpeed, Uint32 lifetime, bool allowMultipleBullets=false);


    private:
        void MovePlayer(float deltaTime, float turnInput, float forwardInput, float screenWidth, float screenHeight);

        float width, height;
        std::vector<float> position, velocity, acceleration;

        float thrustAcceleration;
        float dragConstant;
        float maxSpeed;

        float rotAngle;
        float turnSpeed;

        Polygon* polygon;
        std::vector<Bullet*> bullets;
};

#endif