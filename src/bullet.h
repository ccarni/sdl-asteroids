#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include <vector>

class Bullet {
    public:

        Bullet(float initialX, float initialY, float speed, float angle, Uint32 lifetime);
        ~Bullet();
        void Update(float deltaTime, float screenWidth, float screenHeight);
        void Draw(SDL_Renderer *renderer);

        bool GetFiring();

    private:
        std::vector<float> position, velocity, acceleration;
        float rotAngle; 
        float _speed;
        Uint32 _lifetime;
        Uint32 startTime;
        bool firing; 
};

#endif