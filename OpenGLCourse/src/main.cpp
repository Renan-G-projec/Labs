// Ad Maiorem Dei Gloriam!

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "core/renderer.hpp"
#include "core/camera.hpp"
#include "core/shader.hpp"
#include "core/mesh.hpp"
#include "core/log.hpp"
#include "core/texture.hpp"

int main()
{
    if (!glfwInit())
    {
        Log::log_error("Could not init GLFW.");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    PerspectiveCamera cam{ glm::vec2{ 1280.0f, 720.0f } };

    Renderer renderer;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Course", NULL, NULL);
    if (!window)
    {
        Log::log_error("Could not create GLFW window.");
        return 1;
    }

    cam.lockWindow(window);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        Log::log_error("Could not load OpenGl functions.");
        return 2;
    }

    glViewport(0, 0, 1280, 720);

    Shader shader{"assets/shaders/phong.vert", "assets/shaders/phong.frag"};

    const std::vector<Vertex> pyramidVertices = {
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        
        { 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f },

        { 0.0f, 1.0f, 0.0f, 0.0f, 0.7071f, -0.7071f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f, 0.7071f, -0.7071f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.7071f, -0.7071f, 1.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f, 0.0f, 0.7071f, -0.7071f, 1.0f, 1.0f },
    };

    const std::vector<GLuint> pyramidIndices = {
        0, 2, 1,
        1, 2, 3,

        4, 6, 5,
        5, 6, 7,

        8, 10, 9,
        9, 10, 11,
    };

    shader.activate();
    Mesh pyramid(pyramidVertices, pyramidIndices);

    TransformComponent pyramidTransform{};

    Texture texture;

    texture.load("assets/textures/wall.jpg"); 
    texture.activate();

    float previousTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window)) { 
        glfwPollEvents();

        float currentTime = glfwGetTime();
        float dt = currentTime - previousTime;
        previousTime = currentTime;

        cam.updateByInputs(window, dt);
        
        renderer.clear();
        shader.setUniformSampler2D(0);
        
        renderer.draw({&shader, &pyramid, &pyramidTransform});
        renderer.drawAll(cam, {0.2f, 0.1f, 0.0f});

        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}