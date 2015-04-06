# Target Files

set(EXAMPLE1_SRC ${PROJECT_SOURCE_DIR}/Example1/Example1.cpp)
set(EXAMPLE2_SRC ${PROJECT_SOURCE_DIR}/Example2/Example2.cpp)

project(SDL2OpenGLExample1)
add_executable(SDL2OpenGLExample1 ${EXAMPLE1_SRC})

project(SDL2OpenGLExample2)
add_executable(SDL2OpenGLExample2 ${EXAMPLE2_SRC})
