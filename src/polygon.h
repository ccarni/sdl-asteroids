#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <SDL2/SDL.h>

class Polygon {
    public:

        
        Polygon();
        Polygon(std::vector<std::vector<float>> _vertices, std::vector<std::vector<int>> _edges);
        ~Polygon();
        
        void AddVertex(std::vector<float> vertex);
        void AddEdge(std::vector<int> edge);
        void Draw(SDL_Renderer *renderer, std::vector<float> offset={0.0f,0.0f});
        void DrawLooped(SDL_Renderer *renderer, float screenWidth, float screenHeight, std::vector<float> offset={0.0f,0.0f});

        std::vector<std::vector<float>> GetVertices();
        std::vector<std::vector<int>> GetEdges();

        void SetVertex(int index, std::vector<float> vertex);
        void SetEdge(int index, std::vector<int> edge);

        std::vector<float> GetEdgeNormal(int edgeIndex);

    private:
        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<int>> edges;
        std::vector<float> LoopPosition(std::vector<float> position, float width, float height);
};

#endif