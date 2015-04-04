# Linked libraries

# For windows we're linking the libraries
# in the code with a #pragma comment.
if (APPLE)
# Attempt to find any framework libraries
# if we're on Mac. These libraries are also
# located in the externals/libs folder which
# could be placed in your /Libraries/Frameworks
# directory.
find_library(OpenGLLib OpenGL)
find_library(SDL2Lib SDL2)

# Set the frameworks used
set(FRAMEWORKS
    ${OpenGLLib}
    ${SDL2Lib}
)
endif(APPLE)