// Ad Maiorem Dei Gloriam!
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "core/transform.hpp"
#include "core/shader.hpp"
#include "core/camera.hpp"
#include "core/mesh.hpp"

#include <memory>

struct DrawCommand final
{
    Shader *shader;
    Mesh *mesh;
    TransformComponent *transform;
};

struct InstancedDrawCommand final
{
    Shader *shader;
    InstancedMesh *mesh;
};

class Renderer final
{
public:
    void clear() const;
    void draw(const DrawCommand&);
    void drawInstanced(const InstancedDrawCommand&);
    void drawAll(const PerspectiveCamera&, const glm::vec3 ambientLight = { 0.2f, 0.2f, 0.2f });

private:
    std::vector<DrawCommand> mDrawCommands;
    std::vector<InstancedDrawCommand> mInstancedDrawCommands;

    void sortDrawCommands();
};

#endif