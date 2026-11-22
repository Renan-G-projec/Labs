// Ad Maiorem Dei Gloriam!
#include "core/material.hpp"

void Material::use(Shader& shader)
{
    shader.activate();
    shader.setUniformFloat(mSpecularIntensity, "uMaterial.specularIntensity");
    shader.setUniformFloat(mShineness, "uMaterial.shineness");
}