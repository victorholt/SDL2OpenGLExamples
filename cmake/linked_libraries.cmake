# Linked libraries

# For windows we're linking the libraries
# in the code with a #pragma comment.
if (APPLE)
# Attempt to find any framework libraries
# if we're on Mac. These libraries are also
# located in the externals/libs folder which
# could be placed in your /Libraries/Frameworks
# directory.

# Set the frameworks used
set(FRAMEWORKS
    ${OpenGLLib}
    ${SDL2Lib}
    ${PROJECT_SOURCE_DIR}/externals/libs/OSX/GLFW/libglfw3.a
    ${PROJECT_SOURCE_DIR}/externals/libs/OSX/GL/libGLEW.a
    ${PROJECT_SOURCE_DIR}/externals/libs/OSX/assimp/libassimp.dylib
)
endif(APPLE)

if (WIN32)
link_libraries(
    mingw32
    opengl32
    ${PROJECT_SOURCE_DIR}/externals/libs/Win32/SDL2/libSDL2main.a
    ${PROJECT_SOURCE_DIR}/externals/libs/Win32/SDL2/libSDL2.a
    ${PROJECT_SOURCE_DIR}/externals/libs/Win32/SDL2/libSDL2-2.0.dll.a
    ${PROJECT_SOURCE_DIR}/externals/libs/Win32/GL/libglew32.a
    ${PROJECT_SOURCE_DIR}/externals/libs/Win32/GL/libglew32.dll.a
    m
    dinput8
    dxguid
    dxerr8
    user32
    gdi32
    winmm
    imm32
    ole32
    oleaut32
    shell32
    version
    uuid
)
endif(WIN32)
