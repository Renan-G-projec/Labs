// Ad Maiorem Dei Gloriam!
#include <vector>
#include <algorithm>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "core/renderer.hpp"

void Renderer::clear(const glm::vec3 color) const
{
    glClearColor(color.x, color.y, color.z, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const DrawCommand& command)
{
    mDrawCommands.emplace_back(command);
}

void Renderer::drawInstanced(const InstancedDrawCommand& command)
{
    mInstancedDrawCommands.emplace_back(command);
}

void Renderer::drawAll(const PerspectiveCamera& camera, const Scene& scene)
{
    sortDrawCommands();

    if (mDrawCommands.empty() && mInstancedDrawCommands.empty()) return;

    Shader *currentShader = nullptr;
    Mesh *currentMesh = nullptr;
    glm::mat4 cameraMatrix = camera.getMatrix();

    for (const DrawCommand &drawCommand : mDrawCommands)
    {
        glm::mat4 modelMatrix = drawCommand.transform->calculateMatrix();

        if (drawCommand.shader != currentShader)
        {
            currentShader = drawCommand.shader;
            currentShader->activate();

            currentShader->setUniformMatrix(cameraMatrix, "uCamera");

            currentShader->setUniformVec3(scene.directionalLight.direction, "uDirectionalLight.direction");
            currentShader->setUniformVec3(scene.directionalLight.color, "uDirectionalLight.color");
            currentShader->setUniformFloat(scene.ambientLightIntensity, "uDirectionalLight.intensity");

            currentShader->setUniformVec3(scene.pointLight.color, "uPointLight.color");
            currentShader->setUniformVec3(scene.pointLight.position, "uPointLight.position");
            currentShader->setUniformFloat(scene.pointLight.ambientIntensity, "uPointLight.ambient_intensity");
            currentShader->setUniformFloat(scene.pointLight.intensity, "uPointLight.intensity");
            currentShader->setUniformFloat(scene.pointLight.quadratic, "uPointLight.quadratic");
            currentShader->setUniformFloat(scene.pointLight.linear, "uPointLight.linear");
            currentShader->setUniformFloat(scene.pointLight.constant, "uPointLight.constant");

            currentShader->setUniformVec3(scene.ambientLightColor, "uAmbientLightColor");
            currentShader->setUniformFloat(scene.ambientLightIntensity, "uAmbientLightIntensity");
            currentShader->setUniformVec3(camera.getPosition(), "viewerPos");
        }

        if (drawCommand.mesh != currentMesh)
        {
            currentMesh = drawCommand.mesh;
            currentMesh->lazyBind();
        }

        drawCommand.material->use(*currentShader);
        
        currentShader->setUniformMatrix(modelMatrix, "uModel");
        currentMesh->lazyRender();
    }

    for (const InstancedDrawCommand &drawCommand : mInstancedDrawCommands)
    {
        if (drawCommand.shader != currentShader)
        {
            currentShader = drawCommand.shader;
            currentShader->activate();

            currentShader->setUniformMatrix(cameraMatrix, "uCamera");
            
            currentShader->setUniformVec3(scene.directionalLight.direction, "uDirectionalLight.direction");
            currentShader->setUniformVec3(scene.directionalLight.color, "uDirectionalLight.color");
            currentShader->setUniformFloat(scene.ambientLightIntensity, "uDirectionalLight.intensity");

            currentShader->setUniformVec3(scene.pointLight.color, "uPointLight.color");
            currentShader->setUniformVec3(scene.pointLight.position, "uPointLight.position");
            currentShader->setUniformFloat(scene.pointLight.ambientIntensity, "uPointLight.ambient_intensity");
            currentShader->setUniformFloat(scene.pointLight.intensity, "uPointLight.intensity");
            currentShader->setUniformFloat(scene.pointLight.quadratic, "uPointLight.quadratic");
            currentShader->setUniformFloat(scene.pointLight.linear, "uPointLight.linear");
            currentShader->setUniformFloat(scene.pointLight.constant, "uPointLight.constant");

            currentShader->setUniformFloat(scene.ambientLightIntensity, "uAmbientColorIntensity");
            currentShader->setUniformVec3(scene.ambientLightColor, "uAmbientLightColor");
            currentShader->setUniformVec3(camera.getPosition(), "viewerPos");

        }

        drawCommand.mesh->renderInstanced();
    }

    mInstancedDrawCommands.clear();
    mDrawCommands.clear();
}

void Renderer::sortDrawCommands() 
{
    std::sort(mDrawCommands.begin(), mDrawCommands.end(), [](const DrawCommand &firstCommand, const DrawCommand &secondCommand){
        if (firstCommand.shader != secondCommand.shader) return firstCommand.shader < secondCommand.shader;
        if (firstCommand.mesh != secondCommand.mesh) return firstCommand.mesh < secondCommand.mesh;
        return false;
    });
}