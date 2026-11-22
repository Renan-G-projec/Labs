// Ad Maiorem Dei Gloriam!
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "core/transform.hpp"
#include "core/shader.hpp"
#include "core/camera.hpp"
#include "core/mesh.hpp"
#include "core/material.hpp"

#include "core/scene.hpp"

struct DrawCommand final
{
    Shader *shader;
    Mesh *mesh;
    Material *material;
    TransformComponent *transform;
};

struct InstancedDrawCommand final
{
    Shader *shader;
    Material *material;
    InstancedMesh *mesh;
};

class Renderer final
{
public:
    void clear(const glm::vec3 color = {0.0f, 0.0f, 0.0f}) const;
    void draw(const DrawCommand&);
    void drawInstanced(const InstancedDrawCommand&);
    void drawAll(const PerspectiveCamera&, const Scene&);

private:
    std::vector<DrawCommand> mDrawCommands;
    std::vector<InstancedDrawCommand> mInstancedDrawCommands;

    void sortDrawCommands();
};

#endif