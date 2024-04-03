#pragma once
#include <SDL.h>
#include <vector>
#include <chrono>

struct Point2D { float x; float y; };
struct Point3D { float x; float y; float z; };
struct Edge { int start; int end; };

class Renderer3D
{
public:
    Renderer3D(SDL_Renderer* renderer, const std::vector<Point3D>& points, const std::vector<Edge>& edges, int windowWidth, int windowHeight);
    void render();
    void update(float deltaTime); // Function to update the pyramid's scale

private:
    Point2D projection(Point3D point);
    float FL = 5;
    float DeltaTime = 0;
    float scale = 1.0f; // Scaling factor for the pyramid
    int WindowSizeX;
    int WindowSizeY;
    SDL_Renderer* SDL_render;
    std::vector<Point3D> points;
    std::vector<Edge> edges;
};
