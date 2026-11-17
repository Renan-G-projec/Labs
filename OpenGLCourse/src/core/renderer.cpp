// Ad Maiorem Dei Gloriam!
#include <vector>
#include <algorithm>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "core/renderer.hpp"

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const DrawCommand &command)
{
    mDrawCommands.emplace_back(command);
}

void Renderer::drawAll(const Camera& camera, const glm::vec3 ambientLight)
{
    sortDrawCommands();

    if (mDrawCommands.empty()) return;

    Shader *currentShader = nullptr;
    Mesh *currentMesh = nullptr;
    glm::mat4 cameraMatrix = camera.getMatrix();

    for (const DrawCommand &drawCommand : mDrawCommands)
    {
        glm::mat4 modelMatrix{1.0f};
        modelMatrix = glm::translate(modelMatrix, drawCommand.transform->position);
        modelMatrix = glm::scale(modelMatrix, drawCommand.transform->scale);

        if (drawCommand.shader != currentShader)
        {
            currentShader = drawCommand.shader;
            currentShader->activate();

            currentShader->setUniformVec3({ 10.0f, 10.0f, 2.0f}, "lightPos");
            currentShader->setUniformVec3(ambientLight, "ambientLight");
        }

        if (drawCommand.mesh != currentMesh)
        {
            currentMesh = drawCommand.mesh;
            currentMesh->lazyBind();
        }

        currentShader->setUniformMatrix(cameraMatrix * modelMatrix);
        currentMesh->lazyRender();
    }
    

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