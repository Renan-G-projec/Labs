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

class Renderer final
{
public:
    void clear() const;
    void draw(const DrawCommand&);
    void drawAll(const Camera&, const glm::vec3 ambientLight = { 0.2f, 0.2f, 0.2f });

private:
    std::vector<DrawCommand> mDrawCommands;

    void sortDrawCommands();
};

#endif