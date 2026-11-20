// Ad Maiorem Dei Gloriam!
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>
#include <glad/gl.h>

#include "core/transform.hpp"

#include "core/vertex.hpp"
#include "core/vbo.hpp"
#include "core/ebo.hpp"
#include "core/vao.hpp"


class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    Mesh(const std::string& file);

    void render();
    void lazyRender();
    void lazyBind(); 

    size_t getIndexCount() const { return mIndices.size(); }

private:
    VBO mVbo;
    EBO mEbo;
    VAO mVao;

    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndices;
};

class InstancedMesh
{
public:
    InstancedMesh(Mesh&& mesh, std::vector<TransformComponent> transforms);
    InstancedMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<TransformComponent> transforms);
    InstancedMesh(const std::string& file, std::vector<TransformComponent> transforms);

    void renderInstanced();

private:
    VBO mModelsVBO;

    Mesh mMesh;
    std::vector<glm::mat4> mModels;
};

#endif