#include "asteroid.h"
#include "polygon.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <random>

void Asteroid::Init() {
    radius = (_minRadius + _maxRadius)/2.0f;
    size = roundf(radius / 10.0f); 
    acceleration = {0.0f, 0.0f};
    polygon = new Polygon();
    mass = 10;
    MakeAsteroid(_minRadius, _maxRadius, _stepSize, _stepDeviation);
};

Asteroid::Asteroid(float x, float y, float velocityX, float velocityY) {
    position = {x, y};
    velocity = {velocityX, velocityY};
    _minRadius = 10;
    _maxRadius = 15;
    _stepSize = 1;
    _stepDeviation = 0.5;
    Init();
};

Asteroid::Asteroid(float minRadius, float maxRadius, float stepSize, float stepDeviation, float x, float y, float velocityX, float velocityY) {
    position = {x, y};
    velocity = {velocityX, velocityY};
    _minRadius = minRadius;
    _maxRadius = maxRadius;
    _stepSize = stepSize;
    _stepDeviation = stepDeviation;
    Init();
};

Asteroid::~Asteroid() {
    delete polygon;
};

void Asteroid::Update(float deltaTime, float screenWidth, float screenHeight) {
    velocity[0] += acceleration[0] * deltaTime;
    velocity[1] += acceleration[1] * deltaTime;

    position[0] += velocity[0] * deltaTime;
    position[1] -= velocity[1] * deltaTime; // inverted coordinates

    //loop
    position[0] = fmod(fmod(position[0], screenWidth) + screenWidth, screenWidth);
    position[1] = fmod(fmod(position[1], screenHeight) + screenHeight, screenHeight);
};

void Asteroid::Draw(SDL_Renderer *renderer) {
    polygon->Draw(renderer, position);
}

void Asteroid::MakeAsteroid(float minRadius, float maxRadius, float stepSize, float stepDeviation) {
    float currentAngle = 0.0f;
    // get seed from random hardware device
    std::random_device randomDevice;
    // seed engine
    std::mt19937 gen(randomDevice()); 

    if (stepSize <= stepDeviation) {
        std::cout << "Step deviation must be less than step size\n";
        return; 
    }

    std::uniform_real_distribution<float> radiusDistribution(minRadius, maxRadius);
    std::uniform_real_distribution<float> stepDistribution(stepSize - stepDeviation, stepSize + stepDeviation);

    float stepRadius = radiusDistribution(gen);
    float stepAngle = stepDistribution(gen); 
    currentAngle += stepAngle;

    int i = 0;
    while (currentAngle < 2*M_PI) {

        polygon->SetVertex(i, {stepRadius * (float)cos(currentAngle), stepRadius * (float)sin(currentAngle)});
        if (i > 0) {
            polygon->SetEdge(i-1, {i-1, i});
        }

        stepRadius = radiusDistribution(gen);
        stepAngle = stepDistribution(gen); 
        currentAngle += stepAngle;
        i++;
    };

    polygon->SetEdge(i-1, {i-1, 0});

};