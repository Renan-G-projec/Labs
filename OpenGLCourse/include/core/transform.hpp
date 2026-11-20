// Ad Maiorem Dei Gloriam!
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct TransformComponent
{
    glm::vec3 position{0.0f, 0.0f, 0.0f}; // Position in the world
    glm::vec3 scale{1.0f, 1.0f, 1.0f}; 

    glm::mat4 calculateMatrix() const 
    {
        glm::mat4 mat{1.0};
        mat = glm::translate(mat, position);
        mat = glm::scale(mat, scale);
        return mat;
    }
};

#endif