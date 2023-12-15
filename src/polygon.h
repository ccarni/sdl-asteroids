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
        void Draw(SDL_Renderer *renderer);

        std::vector<std::vector<float>> GetVertices();
        std::vector<std::vector<int>> GetEdges();

        void SetVertex(int index, std::vector<float> vertex);
        void SetEdge(int index, std::vector<int> edge);

    private:
        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<int>> edges;
};

#endif