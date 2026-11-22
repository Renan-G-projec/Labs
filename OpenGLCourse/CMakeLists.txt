# Ad Maiorem Dei Gloriam!
cmake_minimum_required(VERSION 3.12)

project(OpenGLCourse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetching the contents
include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_WAYLAND OFF)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master
)

set(CGLM_SHARED OFF)
set(CGLM_STATIC ON)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
)

FetchContent_MakeAvailable(glfw glm)

# Actual compiling
add_executable(OpenGLCourse)

find_package(OpenGL REQUIRED)

target_sources(OpenGLCourse PRIVATE
    src/main.cpp
    
    src/core/renderer.cpp
    src/core/mesh.cpp
    src/core/vao.cpp
    src/core/vbo.cpp
    src/core/ebo.cpp
    src/core/camera.cpp
    src/core/shader.cpp
    src/core/texture.cpp
    src/core/material.cpp

    external/stb/stb_image.cpp
    external/glad/src/gl.c
)

target_include_directories(OpenGLCourse PRIVATE
    "include"
    "external/glad/include"
    "external/stb"
)

target_link_libraries(OpenGLCourse PRIVATE glfw glm OpenGL::GL)