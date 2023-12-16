#ifndef ASTEROID_H
#define ASTEROID_H

#include "polygon.h"
#include <SDL2/SDL.h>
#include <vector>

class Asteroid {
    public:

        Asteroid(float x, float y, float velocityX, float velocityY);
        Asteroid(float minRadius, float maxRadius, float stepSize, float stepDeviation, float x, float y, float velocityX, float velocityY);
        ~Asteroid();
        void Init();
        void Update(float deltaTime, float windowWidth, float windowHeight);
        void Draw(SDL_Renderer *renderer);
        void MakeAsteroid(float minRadius, float maxRadius, float stepSize, float stepDeviation);

    private:
        std::vector<float> position, velocity, acceleration; 

        float _minRadius, _maxRadius, radius;
        float _stepSize, _stepDeviation;
        int size;
        float mass;
        // Asteroid *split1, *split2;

        Polygon *polygon;

        void Split();
};

#endif