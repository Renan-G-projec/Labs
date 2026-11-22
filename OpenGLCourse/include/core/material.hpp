// Ad Maiorem Dei Gloriam!
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glad/gl.h>
#include "shader.hpp"

class Material
{
public:
    Material(GLfloat specularIntensity, GLfloat shineness)
        : mSpecularIntensity{specularIntensity}, mShineness{shineness} {};

    virtual void use(Shader&);

private:
    GLfloat mSpecularIntensity;
    GLfloat mShineness;
};

#endif