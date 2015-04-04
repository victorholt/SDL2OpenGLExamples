/**
 * This example initializes SDL2 and opens up a new
 * window for use with OpenGL in the next example.
 */
#include <iostream>
#include <SDL2/SDL.h>

// Start our application.
int main(int argc, char** argv)
{
    // Flag that lets us know if we
    // should continue running our
    // game loop.
    bool AppRunning = true;

    // Initialize the SDL2 library.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Failed to initialize SDL2" << std::endl;
        return 0;
    }

    // Create our window.
    SDL_Window* sdlWindow = SDL_CreateWindow(
            "SDL2 and OpenGL Examples",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_OPENGL
    );

    // Start our game loop.
    SDL_Event EventMsg;
    while (AppRunning)
    {
        while (SDL_PollEvent(&EventMsg))
        {
            if (EventMsg.type == SDL_QUIT)
            {
                AppRunning = false;
            }
        }
    }

    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}