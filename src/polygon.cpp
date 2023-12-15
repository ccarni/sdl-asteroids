#include "polygon.h"
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

Polygon::Polygon() {
    vertices = {{0.0f, 0.0f}, {0.0f, 0.0f}};
    edges = {{0,1}};
};

Polygon::Polygon(std::vector<std::vector<float>> _vertices, std::vector<std::vector<int>> _edges) {
    vertices = _vertices;
    edges = _edges;
};
        
Polygon::~Polygon() {
    
};
        
void Polygon::AddVertex(std::vector<float> vertex) {
    vertices.push_back(vertex);
};
void Polygon::AddEdge(std::vector<int> edge) {
    edges.push_back(edge);
};

void Polygon::Draw(SDL_Renderer *renderer) {
    for (std::vector<int> edge : edges){
        SDL_RenderDrawLineF(renderer, vertices[edge[0]][0], vertices[edge[0]][1], vertices[edge[1]][0], vertices[edge[1]][1]);
    }
}

std::vector<std::vector<float>> Polygon::GetVertices() {
    return vertices;
};
std::vector<std::vector<int>> Polygon::GetEdges() {
    return edges;
};

void Polygon::SetVertex(int index, std::vector<float> vertex) {
    if (index > vertices.size() || index < 0) {
        std::cout << "index outside range of array + 1\n";
    } else if (index == vertices.size()) {
        vertices.push_back(vertex);
    } else {
        vertices[index] = vertex;
    }
};

void Polygon::SetEdge(int index, std::vector<int> edge) {
    if (index > edges.size() || index < 0) {
        std::cout << "index outside range of array + 1\n";
    } else if (index == edges.size()) {
        edges.push_back(edge);
    } else {
        edges[index] = edge;
    }
};
