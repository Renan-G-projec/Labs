// Ad Maiorem Dei Gloriam!
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>

struct DirectionalLight final
{
    glm::vec3 direction = {0.0f, -1.0f, 0.0f};
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
    float intensity = 1.0f;
};


struct PointLight final 
{
    glm::vec3 position{0.0f};
    glm::vec3 color{1.0f};
    float ambientIntensity = 0.1f;
    float intensity = 1.0f;
    float quadratic = 1.0f;
    float linear = 1.0f;
    float constant = 1.0f;
};

#endif