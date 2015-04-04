# Target Files

set(EXAMPLE1_SRC ${PROJECT_SOURCE_DIR}/Example1/Example1.cpp)

# Link the GLew and AssImp libraries.
set(AssImpLib
    ${PROJECT_SOURCE_DIR}/EnfinityCube/Deps/Libs/assimp/libassimp.dylib
)

set(GLewLib
    ${PROJECT_SOURCE_DIR}/EnfinityCube/Deps/Libs/GL/libGLEW.a
)

project(SDL2OpenGLExample1)
add_executable(SDL2OpenGLExample1 ${EXAMPLE1_SRC})
target_link_libraries(SDL2OpenGLExample1 ${FRAMEWORKS})