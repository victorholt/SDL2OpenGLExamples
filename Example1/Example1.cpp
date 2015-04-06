/**
 * This example initializes SDL2 and opens up a new
 * window for use with OpenGL in the next example.
 */

#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Start our application.
int main(int argc, char** argv)
{

    // Flag that lets us know if we
    // should continue running our
    // game loop.
    bool AppRunning = true;

    // Initialize the SDL2 library.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL2" << std::endl;
        return 0;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create our window.
    SDL_Window* sdlWindow = SDL_CreateWindow(
            "SDL2 and OpenGL Examples",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_OPENGL
    );

    // Create our OpenGL context.
    SDL_GLContext sdlGLContext = SDL_GL_CreateContext(sdlWindow);

    // Initialize GLew
    glewExperimental = true;
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        std::cerr << "GLEW error: " << glewGetErrorString(glewStatus) << std::endl;
        exit(1);
    }

    // Start our game loop.
    SDL_Event EventMsg;
    while (AppRunning)
    {
        // Render our triangle.
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the depth buffer.
        SDL_GL_SwapWindow(sdlWindow);

        while (SDL_PollEvent(&EventMsg))
        {
            if (EventMsg.type == SDL_QUIT)
            {
                AppRunning = false;
            }
        }
    }

    SDL_GL_DeleteContext(sdlGLContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}
