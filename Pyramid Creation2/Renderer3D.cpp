#include "Renderer3D.h"
#include <SDL.h>
#include <cmath>

Renderer3D::Renderer3D(SDL_Renderer* renderer, const std::vector<Point3D>& _points, const std::vector<Edge>& _edges, int windowWidth, int windowHeight)
    : WindowSizeX(windowWidth), WindowSizeY(windowHeight) // Initialize window size variables
{
    SDL_render = renderer;
    points = _points;
    edges = _edges;
}


void Renderer3D::render()
{
    auto time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration(0);

    SDL_SetRenderDrawColor(SDL_render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(SDL_render);
    SDL_SetRenderDrawColor(SDL_render, 255, 192, 203, SDL_ALPHA_OPAQUE);

    for (auto& edge : edges) {
        Point2D start = projection(points[edge.start]);
        Point2D end = projection(points[edge.end]);

        SDL_RenderDrawLine(SDL_render, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(SDL_render);

    auto time2 = std::chrono::high_resolution_clock::now();
    duration = time2 - time1;
    DeltaTime += duration.count(); // Accumulate elapsed time
}

void Renderer3D::update(float deltaTime) {
    // Example: Make the pyramid grow/shrink over time
    // Calculate scale factor based on time (e.g., sinusoidal function)
    scale = 1.0f + std::sin(deltaTime) * 0.5f; // Use deltaTime parameter for updating scale
}

Point2D Renderer3D::projection(Point3D point)
{
    // Calculate the center of the window
    float centerX = WindowSizeX / 2.0;
    float centerY = WindowSizeY / 2.0;

    // Calculate the projected coordinates with scale applied
    float projectedX = centerX + (point.x * FL) / (FL + point.z) * 100 * scale;
    float projectedY = centerY + (point.y * FL) / (FL + point.z) * 100 * scale;

    return Point2D{ projectedX, projectedY };
}
