# Target Files

set(EXAMPLE1_SRC ${PROJECT_SOURCE_DIR}/Example1/Example1.cpp)
set(EXAMPLE2_SRC ${PROJECT_SOURCE_DIR}/Example2/Example2.cpp)

# Link the GLew and AssImp libraries.
set(AssImpLib
    ${PROJECT_SOURCE_DIR}/externals/libs/OSX/assimp/libassimp.dylib
)

set(GLewLib
    ${PROJECT_SOURCE_DIR}/externals/libs/OSX/GL/libGLEW.a
)

project(SDL2OpenGLExample1)
add_executable(SDL2OpenGLExample1 ${EXAMPLE1_SRC})
target_link_libraries(SDL2OpenGLExample1 ${FRAMEWORKS})

project(SDL2OpenGLExample2)
add_executable(SDL2OpenGLExample2 ${EXAMPLE2_SRC})
target_link_libraries(SDL2OpenGLExample2 ${FRAMEWORKS} ${GLewLib})