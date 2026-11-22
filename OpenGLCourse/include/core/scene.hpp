// Ad Maiorem Dei Gloriam!
#ifndef SCENE_HPP
#define SCENE_HPP

#include <glm/vec3.hpp>
#include "core/light.hpp"

struct Scene final
{
    glm::vec3 ambientLightColor = {1.0f, 1.0f, 1.0f};
    float ambientLightIntensity = 0.2f;
    
    DirectionalLight directionalLight;
    PointLight pointLight;
};

#endif