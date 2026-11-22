// Ad Maiorem Dei Gloriam!

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "core/renderer.hpp"
#include "core/camera.hpp"
#include "core/shader.hpp"
#include "core/mesh.hpp"
#include "core/log.hpp"
#include "core/texture.hpp"

Mesh createSphere(unsigned int radius)
{
    std::vector<Vertex> sphereVertices;
    std::vector<GLuint> sphereIndices;


    const unsigned int X_SEGMENTS = 8;
    const unsigned int Y_SEGMENTS = 8;
    const float PI = 3.14159265359f;

    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * radius;
            float yPos = std::cos(ySegment * PI) * radius;
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * radius;

            sphereVertices.push_back({
                xPos, yPos, zPos,    
                xPos, yPos, zPos,   
                xSegment, ySegment   
            });
        }
    }

    for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
        for (unsigned int x = 0; x < X_SEGMENTS; ++x) {
            GLuint first  = y * (X_SEGMENTS + 1) + x;
            GLuint second = first + X_SEGMENTS + 1;

            sphereIndices.push_back(first);
            sphereIndices.push_back(second);
            sphereIndices.push_back(first + 1);

            sphereIndices.push_back(second);
            sphereIndices.push_back(second + 1);
            sphereIndices.push_back(first + 1);
        }
    }

    return Mesh{sphereVertices, sphereIndices};
}

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

    Scene scene = {{1.0f, 1.0f, 1.0f}, 0.1f};
    scene.pointLight.position = {0.0f, 2.0f, 2.0f};

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
    shader.activate();

    Texture texture;
    texture.load("assets/textures/wall.jpg"); 
    texture.activate();

    Mesh sphere = createSphere(1);
    TransformComponent sphereTransform{};

    Material material{10.0, 32};

    float previousTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window)) { 
        glfwPollEvents();

        
        float currentTime = glfwGetTime();
        float dt = currentTime - previousTime;
        previousTime = currentTime;

        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) scene.pointLight.position.y += 32 * dt;
        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) scene.pointLight.position.y -= 32 * dt;

        cam.updateByInputs(window, dt);
        
        renderer.clear({0.2f, 0.35f, 0.5f});
        shader.setUniformSampler2D(0);
        
        renderer.draw({&shader, &sphere, &material, &sphereTransform});
        renderer.drawAll(cam, scene);

        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
