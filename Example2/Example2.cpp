/**
 * This example initializes SDL2 and opens up a new
 * window for use with OpenGL in the next example.
 */
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

std::string PROJECT_BASEPATH = "./../";

// Structure containing the triangle
// vertex information.
union Vertex
{
    Vertex(GLfloat vecx, GLfloat vecy, GLfloat vecz)
    {
        x = vecx;
        y = vecy;
        z = vecz;
    }

    struct
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };

    GLfloat v[3];
};

// Create the vertex buffer object to render the triangle.
GLuint VertexBufferObject;
GLuint VertexBufferArray;

Vertex vertices[3] =
        {
                {-0.5f, -0.5f, 0.0f},
                {0.0f, 1.0f, 0.0f},
                {0.5f, -0.5f, 0.0f}
        };

void CreateVBO()
{
    glGenVertexArrays(1, &VertexBufferObject);
    glBindVertexArray(VertexBufferObject);

    glGenBuffers(1, &VertexBufferArray);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferArray);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 3, &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

// Render the triangle.
void DrawTriangle()
{
    glBindVertexArray(VertexBufferArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

// Clean up the vertex array/object buffers.
void CleanupVBO()
{
    glDeleteBuffers(1, &VertexBufferObject);
    glDeleteVertexArrays(1, &VertexBufferArray);
}

// Sets up the Vertex/Fragment shaders.
std::string ReadFile(std::string FilePath)
{
    std::string output;
    std::string line;

    std::ifstream file;
    file.open(FilePath);

    if (file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }

        file.close();
        return output;
    }
    else
    {
        std::cerr << "Unable to find shader @: " + FilePath << std::endl;
        return "";
    }
}

// Check for shader program errors.
void CheckShaderErr(GLuint shader, GLuint flag, bool isProgram)
{
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram)
    {
        glGetProgramiv(shader, flag, &success);
    }
    else
    {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE)
    {
        if (isProgram)
        {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        }
        else
        {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }

        std::cerr << error << std::endl;
    }
}

GLuint ShaderProgram;
GLuint VertexShader;
GLuint FragmentShader;
bool LoadShaders()
{
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!VertexShader || !FragmentShader)
    {
        return false;
    }

    std::string VertexShaderStr = ReadFile(PROJECT_BASEPATH + "Example2/vertex_shader.glsl");
    std::string FragmentShaderStr = ReadFile(PROJECT_BASEPATH + "Example2/fragment_shader.glsl");

    const GLchar* vertShaderString;
    GLint vertShaderLength;

    const GLchar* fragShaderString;
    GLint fragShaderLength;

    vertShaderString = VertexShaderStr.c_str();
    vertShaderLength = VertexShaderStr.length();

    fragShaderString = FragmentShaderStr.c_str();
    fragShaderLength = FragmentShaderStr.length();

    glShaderSource(VertexShader, 1, &vertShaderString, &vertShaderLength);
    glCompileShader(VertexShader);
    CheckShaderErr(VertexShader, GL_COMPILE_STATUS, false);

    glShaderSource(FragmentShader, 1, &fragShaderString, &fragShaderLength);
    glCompileShader(FragmentShader);
    CheckShaderErr(FragmentShader, GL_COMPILE_STATUS, false);

    // Create our shader program.
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);

    glBindAttribLocation(ShaderProgram, 0, "position");

    glLinkProgram(ShaderProgram);
    CheckShaderErr(ShaderProgram, GL_LINK_STATUS, true);

    glValidateProgram(ShaderProgram);
    CheckShaderErr(ShaderProgram, GL_VALIDATE_STATUS, true);

    return true;
}

// Clean up shader program.
void CleanupShaders()
{
    glDetachShader(ShaderProgram, VertexShader);
    glDeleteShader(VertexShader);

    glDetachShader(ShaderProgram, FragmentShader);
    glDeleteShader(FragmentShader);

    glDeleteProgram(ShaderProgram);
}

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

    // Render settings.
    glEnable(GL_DEPTH_TEST);

    // Create our triangle.
    CreateVBO();

    // Load the shaders.
    LoadShaders();

    // Start our game loop.
    SDL_Event EventMsg;
    while (AppRunning)
    {
        // Render our triangle.
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(ShaderProgram);
        DrawTriangle();

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

    CleanupShaders();
    CleanupVBO();

    SDL_GL_DeleteContext(sdlGLContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}
