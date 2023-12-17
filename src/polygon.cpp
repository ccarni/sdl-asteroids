#include "polygon.h"
#include <vector>
#include <cmath>
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

std::vector<float> Polygon::LoopPosition(std::vector<float> position, float width, float height) {
    float loopedX = fmod(fmod(position[0], width) + width, width);
    float loopedY = fmod(fmod(position[1], height) + height, height);
    return {loopedX, loopedY};
}; 

void Polygon::Draw(SDL_Renderer *renderer, std::vector<float> offset) {
    
    for (std::vector<int> edge : edges){
        SDL_RenderDrawLineF(renderer, vertices[edge[0]][0] + offset[0], vertices[edge[0]][1] + offset[1],
                             vertices[edge[1]][0] + offset[0], vertices[edge[1]][1] + offset[1]);
    }
}

void Polygon::DrawLooped(SDL_Renderer *renderer, float screenWidth, float screenHeight, std::vector<float> offset) {
    for (std::vector<int> edge : edges){
        std::vector<float> originalPosition1 = {vertices[edge[0]][0] + offset[0], vertices[edge[0]][1] + offset[1]};
        std::vector<float> originalPosition2 = {vertices[edge[1]][0] + offset[0], vertices[edge[1]][1] + offset[1]};
        std::vector<float> loopedPosition1 = LoopPosition(originalPosition1, screenWidth, screenHeight);
        std::vector<float> loopedPosition2 = LoopPosition(originalPosition2, screenWidth, screenHeight);
        // points from original positions 2 to 1
        std::vector<float> pointAlongEdge = {originalPosition1[0] - originalPosition2[0], originalPosition1[1] - originalPosition2[1]};

        SDL_RenderDrawLineF(renderer, originalPosition1[0], originalPosition1[1],
                                originalPosition2[0], originalPosition2[1]);
        if (originalPosition1 != loopedPosition1) {
            SDL_RenderDrawLineF(renderer, loopedPosition1[0] - pointAlongEdge[0], loopedPosition1[1] - pointAlongEdge[1],
                                loopedPosition1[0], loopedPosition1[1]); 
        }
        if (originalPosition2 != loopedPosition2) {
            SDL_RenderDrawLineF(renderer, loopedPosition2[0] + pointAlongEdge[0], loopedPosition2[1] + pointAlongEdge[1],
                                loopedPosition2[0], loopedPosition2[1]);
        }
        
        
    }
};

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

std::vector<float> Polygon::GetEdgeNormal(int edgeIndex) {
    std::vector<float> point1 = vertices[edges[edgeIndex][0]];
    std::vector<float> point2 = vertices[edges[edgeIndex][0]]; 
    std::vector<float> edgeVector = {point2[0] - point1[0], point2[1] - point1[1]};
    std::vector<float> normalVector = {-edgeVector[1], edgeVector[0]};
    return normalVector;
};
