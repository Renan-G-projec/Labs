// Ad Maiorem Dei Gloriam!
#include "core/vao.hpp"
#include <utility>

VAO::VAO()
{
    glGenVertexArrays(1, &mId);
}


VAO::VAO(VAO&& other) noexcept
    : mId{std::exchange(other.mId, 0)}
{
}

VAO& VAO::operator=(VAO&& other) noexcept
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &mId);
        mId = std::exchange(other.mId, 0);
    }

    return *this;
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &mId);
}

void VAO::setVertexAttribute(int index, GLint numComponents, GLsizei stride, void* componentOffset)
{
    glVertexAttribPointer(index, numComponents, GL_FLOAT, GL_FALSE, stride, componentOffset);
    glEnableVertexAttribArray(index);
}

void VAO::bind()
{
    glBindVertexArray(mId);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}