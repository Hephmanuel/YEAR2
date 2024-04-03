#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL.h>


// Define points and edges for the pyramid
std::vector<Point3D> points{
    {0, 1, 0},  // Top point
    {-1, -1, 1},  // Front left
    {1, -1, 1},  // Front right
    {1, -1, -1},  // Back right
    {-1, -1, -1}  // Back left
};

std::vector<Edge> edges{
    {0, 1}, {0, 2}, {0, 3}, {0, 4},  // Base edges
    {1, 2}, {2, 3}, {3, 4}, {4, 1}   // Side edges
};

// Default C++ function
int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed. SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow("Pyramid Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    if (!window) {
        std::cerr << "Failed to create window. SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer. SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Get window width and height
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Create renderer object for the pyramid with window width and height
    Renderer3D renderer3D(renderer, points, edges, windowWidth, windowHeight);

    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        // Render the pyramid
        renderer3D.render();
        renderer3D.update(0.01f); // Pass a fixed delta time for now
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
