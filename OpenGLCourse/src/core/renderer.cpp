// Ad Maiorem Dei Gloriam!
#include <vector>
#include <algorithm>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "core/renderer.hpp"

void Renderer::clear() const
{
    glClearColor(0.2, 0.2, 0.2, 1.0);
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

void Renderer::drawAll(const PerspectiveCamera& camera, const glm::vec3 ambientLight)
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
            currentShader->setUniformVec3({ 10.0f, 10.0f, 2.0f}, "lightPos");
            currentShader->setUniformVec3(ambientLight, "ambientLight");
            currentShader->setUniformVec3(camera.getPosition(), "viewerPos");
        }

        if (drawCommand.mesh != currentMesh)
        {
            currentMesh = drawCommand.mesh;
            currentMesh->lazyBind();
        }

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
            currentShader->setUniformVec3({ 10.0f, 10.0f, 2.0f}, "lightPos");
            currentShader->setUniformVec3(ambientLight, "ambientLight");
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