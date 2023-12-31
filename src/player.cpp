#include "player.h"
#include "bullet.h"
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

    rotAngle = 0.0f;
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
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
};

void Player::Update(float deltaTime, float turnInput, float forwardInput, float screenWidth, float screenHeight) {
    MovePlayer(deltaTime, turnInput, forwardInput, screenWidth, screenHeight);
    std::vector<int> spentBulletIndeces;
    for (int i = 0; i < bullets.size(); i++) {
        //ADD CHECK CONDITION OR SOMETHING TO DELETE BULLETS
        if (bullets[i]->GetFiring()) {
            bullets[i]->Update(deltaTime, screenWidth, screenHeight);
        } else {
            spentBulletIndeces.push_back(i);
        }
    }

    for (int i = spentBulletIndeces.size()-1; i >= 0; i--) {
        bullets.erase(std::next(bullets.begin(), spentBulletIndeces[i]));
    }

};

void Player::Draw(SDL_Renderer *renderer) {
    polygon->SetVertex(0, { (float)cos(rotAngle) * (width/2.0f), -(float)sin(rotAngle) * (height/2.0f)});
    polygon->SetVertex(1, { -(float)sin(rotAngle + M_PI/4.0f) * (width/2.0f), -(float)cos(rotAngle + M_PI/4.0f) * (height/2.0f)});
    polygon->SetVertex(2, {(float)sin(rotAngle - M_PI/4.0f) * (width/2.0f),(float)cos(rotAngle - M_PI/4.0f) * (height/2.0f)});

    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

    polygon->DrawLooped(renderer, screenWidth, screenHeight, position);

    for (Bullet* bullet : bullets) {
        bullet->Draw(renderer);
    }

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

void Player::Fire(float fireSpeed, Uint32 lifetime, bool allowMultipleBullets) {
    if (!allowMultipleBullets && bullets.size() > 0) {
        return;
    }
    //NOTE: assumes the first position of the polygon is the "tip" position
    bullets.push_back(new Bullet(polygon->GetVertices()[0][0] + position[0], polygon->GetVertices()[0][1] + position[1], fireSpeed, rotAngle, lifetime));
}

