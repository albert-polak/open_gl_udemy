cmake_minimum_required(VERSION 3.14)
project(MyOpenGLApp)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory("external_libs/glfw-3.4")
add_subdirectory("external_libs/glm")

include_directories(
    "external_libs/glfw-3.4/include"
    "external_libs/glew-2.1.0-lib/include"
    "external_libs/glm"
)

link_directories(
    "external_libs/glew-2.1.0-lib/lib/Release/x64"
)

add_executable(
    openglApp
    main.cpp
    mesh.cpp
    shader.cpp
)

target_link_libraries(openglApp PUBLIC
    glew32
    glfw
    opengl32
)