#include "player.h"
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <iostream>

void Player::Init() {
    turnSpeed = 6;
    thrustAcceleration = 3;
    dragConstant = 0.002;
    maxSpeed = 100;
    tipPoint = {0.0f, 0.0f};
    backLeft = {0.0f, 0.0f};
    backRight = {0.0f, 0.0f};
}

Player::Player() {
    position[0] = 0;
    position[1] = 0;
    Init();
}

Player::Player(float _width, float _height) {
    position[0] = 0;
    position[1] = 0;
    width = _width;
    height = _height; 
    Init();
}

Player::Player(float x, float y, float _width, float _height) {
    position[0] = x;
    position[1] = y;
    width = _width;
    height = _height;
    Init();
}

void Player::DrawPlayer(SDL_Renderer *renderer) {
    tipPoint = {position[0] + (float)cos(rotAngle) * (width/2.0f), position[1] - (float)sin(rotAngle) * (height/2.0f)};
    backLeft = {position[0] - (float)sin(rotAngle + M_PI/4.0f) * (width/2.0f), position[1] - (float)cos(rotAngle + M_PI/4.0f) * (height/2.0f)};
    backRight = {position[0] + (float)sin(rotAngle - M_PI/4.0f) * (width/2.0f), position[1] + (float)cos(rotAngle - M_PI/4.0f) * (height/2.0f)};

    SDL_RenderDrawPointF(renderer, position[0], position[1]);
    SDL_RenderDrawLineF(renderer, tipPoint[0], tipPoint[1], backLeft[0], backLeft[1]);
    SDL_RenderDrawLineF(renderer, backLeft[0], backLeft[1], backRight[0], backRight[1]);
    SDL_RenderDrawLineF(renderer, backRight[0], backRight[1], tipPoint[0], tipPoint[1]);
}

void Player::MovePlayer(float deltaTime, float turnInput, float forwardInput, float screenWidth, float screenHeight) {
    rotAngle -= turnInput * turnSpeed * deltaTime;
    
    if (forwardInput == 1) {
        acceleration = {(float)cos(rotAngle) * thrustAcceleration, (float)sin(rotAngle) * thrustAcceleration};
    } else {
        // evaluation to true becomes 1, evaluation to false becomes 0
        int velocitySignX = (velocity[0] > 0) - (velocity[0] < 0);
        int velocitySignY = (velocity[1] > 0) - (velocity[1] < 0);
        acceleration = {-velocitySignX * (float)pow(velocity[0], 2)*dragConstant, -velocitySignY * (float)pow(velocity[1], 2)*dragConstant};
    }

    velocity[0] += acceleration[0];
    velocity[1] += acceleration[1];

    // clamp speed
    float speed = sqrt((float)pow(velocity[0], 2) + (float)pow(velocity[1], 2));
    if (speed > maxSpeed) {
        std::vector<float> unitVelocity = {velocity[0]/speed, velocity[1]/speed};
        velocity[0] = unitVelocity[0] * maxSpeed;
        velocity[1] = unitVelocity[1] * maxSpeed;
    }

    position[0] += velocity[0] * deltaTime;
    position[1] -= velocity[1] * deltaTime; // inverted coordinates

    //loop
    position[0] = fmod(fmod(position[0], screenWidth) + screenWidth, screenWidth);
    position[1] = fmod(fmod(position[1], screenHeight) + screenHeight, screenHeight);
}

void Player::Fire() {

}

