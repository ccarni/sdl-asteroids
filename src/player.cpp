#include "player.h"
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "polygon.h"

void Player::Init() {
    /* 
    Remember Units:
        position: pixels (origin is topleft, positive moving down and right)
        velocity: pixels/second
        acceleration:pixels/(s^2)
    */
    position = {0.0f, 0.0f};
    velocity = {0.0f, 0.0f};
    acceleration = {0.0f, 0.0f};


    turnSpeed = 6;
    maxSpeed = 150;
    thrustAcceleration = 75;
    dragConstant = 0.03;
    polygon = new Polygon();

    polygon->SetEdge(0, {0,1});
    polygon->SetEdge(1, {1,2});
    polygon->SetEdge(2, {2,0});

}

Player::Player() {
    Init();
    width = 10;
    height = 10;
}

Player::Player(float _width, float _height) {
    Init();
    width = _width;
    height = _height; 
}

Player::Player(float x, float y, float _width, float _height) {
    Init();
    position[0] = x;
    position[1] = y;
    width = _width;
    height = _height;
}

Player::~Player() {
    delete polygon;
};

void Player::Draw(SDL_Renderer *renderer) {
    polygon->SetVertex(0, {position[0] + (float)cos(rotAngle) * (width/2.0f), position[1] - (float)sin(rotAngle) * (height/2.0f)});
    polygon->SetVertex(1, {position[0] - (float)sin(rotAngle + M_PI/4.0f) * (width/2.0f), position[1] - (float)cos(rotAngle + M_PI/4.0f) * (height/2.0f)});
    polygon->SetVertex(2, {position[0] + (float)sin(rotAngle - M_PI/4.0f) * (width/2.0f), position[1] + (float)cos(rotAngle - M_PI/4.0f) * (height/2.0f)});

    polygon->Draw(renderer);

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

    velocity[0] += acceleration[0] * deltaTime;
    velocity[1] += acceleration[1] * deltaTime;

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

