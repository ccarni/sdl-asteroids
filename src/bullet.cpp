#include "bullet.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>

Bullet::Bullet(float initialX, float initialY, float speed, float angle, Uint32 lifetime) {
    rotAngle = angle;
    _speed = speed;
    position = {initialX, initialY};
    velocity = {speed * (float)cos(angle), speed * (float)sin(angle)};
    acceleration = {0.0f, 0.0f};
    _lifetime = lifetime;
    startTime = SDL_GetTicks();
    firing = true;

};

Bullet::~Bullet() {

};

void Bullet::Update(float deltaTime, float screenWidth, float screenHeight) {

    
    if (SDL_GetTicks() - startTime > _lifetime) {
        firing = false;
        return;
    }

    velocity[0] += acceleration[0] * deltaTime;
    velocity[1] += acceleration[1] * deltaTime;


    position[0] += velocity[0] * deltaTime;
    position[1] -= velocity[1] * deltaTime; // inverted coordinates

    //loop
    position[0] = fmod(fmod(position[0], screenWidth) + screenWidth, screenWidth);
    position[1] = fmod(fmod(position[1], screenHeight) + screenHeight, screenHeight);

};

void Bullet::Draw(SDL_Renderer *renderer) {
    if (!firing) {
        return;
    }
    SDL_RenderDrawPointF(renderer, position[0], position[1]);
};

bool Bullet::GetFiring() {
    return firing;
};
