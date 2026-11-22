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

    Scene scene{};
    scene.directionalLight.direction = glm::normalize(glm::vec3{0.0f, -1.0f, 100.0f});

    scene.pointLight.intensity = 0.0f;
    scene.ambientLightIntensity = 0.55f;

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
    texture.setWrap(GL_REPEAT, GL_REPEAT);
    texture.setFilters(GL_LINEAR, GL_LINEAR);
    texture.load("assets/textures/wall.jpg"); 
    texture.activate();

    Mesh floorMesh{std::vector<Vertex>{{-1000.0f, 0.0f, -1000.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f}, {-1000.0f, 0.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 100.0f}, {1000.0f, 0.0f, -1000.0f, 0.0f, 1.0f, 0.0f, 100.0f, 0.0f}, {1000.0f, 0.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 100.0f, 100.0f}}, std::vector<GLuint>{0U, 1U, 2U, 1U, 2U, 3U}};
    TransformComponent floorTransform{};

    floorTransform.position.y = -10.0f;

    Material material{2.0, 64.0};

    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    float gravity = 10.0f;

    float previousTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window)) { 
        glfwPollEvents();
        
        float currentTime = glfwGetTime();
        float dt = currentTime - previousTime;
        previousTime = currentTime;

        position.y -= dt * gravity;
        if (position.y <= floorTransform.position.y)
        {
            position.y = floorTransform.position.y;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += cam.getOrientation() * 10.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= cam.getOrientation() * 10.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += cam.getRight() * 10.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= cam.getRight() * 10.0f * dt;

        cam.setPosition(position + glm::vec3{0.0f, 10.0f, 0.0f});

        cam.updateRotationByMouse(window, dt);
        
        renderer.clear({0.2f, 0.35f, 0.5f});
        shader.setUniformSampler2D(0);
        
        renderer.draw({&shader, &floorMesh, &material, &floorTransform});
        renderer.drawAll(cam, scene);

        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
