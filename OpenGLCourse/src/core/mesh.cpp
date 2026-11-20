// Ad Maiorem Dei Gloriam!
#include "core/mesh.hpp" 
#include "core/log.hpp"

#include <algorithm>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
    : mVertices(vertices), mIndices(indices)
{
    mVao.bind();
    mVbo.bind();
    mEbo.bind();

    mVbo.sendData(vertices);
    mEbo.sendData(indices);

    mVao.setVertexAttribute(0, 3, sizeof(Vertex)); // Position
    mVao.setVertexAttribute(1, 3, sizeof(Vertex), (void*)(offsetof(Vertex, normal))); // Normal
    mVao.setVertexAttribute(2, 2, sizeof(Vertex), (void*)(offsetof(Vertex, uv))); // UV
    
    mVao.unbind();
    mVbo.unbind();
    mEbo.unbind();
}

Mesh::Mesh(const std::string& filename)
{
    Log::log_debug("Warning: tried to load a file (" + filename + ") but object loading is not supported yet.");
}

void Mesh::render()
{
    mVao.bind();
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void Mesh::lazyRender() 
{
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void Mesh::lazyBind()
{
    mVao.bind();
}

InstancedMesh::InstancedMesh(Mesh&& mesh, std::vector<TransformComponent> transforms)
    : mMesh{std::move(mesh)}
{
    mModels.reserve(transforms.size());
    for (const auto& transform : transforms)
    {
        mModels.push_back(transform.calculateMatrix()); 
    }

    mMesh.lazyBind();
    mModelsVBO.sendData(mModels);

    for (uint8_t i = 0; i < 4; ++i)
    {
        glVertexAttribPointer(i + 3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(i * sizeof(glm::vec4)));
        glEnableVertexAttribArray(i + 3);
        glVertexAttribDivisor(i + 3, 1);
    }

    glBindVertexArray(0);
}

void InstancedMesh::renderInstanced()
{
    mMesh.lazyBind();

    glDrawElementsInstanced(GL_TRIANGLES, mMesh.getIndexCount(), GL_UNSIGNED_INT, (void*)0, mModels.size());
}