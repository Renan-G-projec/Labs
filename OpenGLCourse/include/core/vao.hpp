// Ad Maiorem Dei Gloriam!
#ifndef VAO_HPP
#define VAO_HPP

#include <glad/gl.h>
class VAO 
{
public:
    VAO();
    VAO(const VAO& other) = delete;
    VAO& operator=(const VAO&) = delete;

    VAO(VAO&& other) noexcept;
    VAO& operator=(VAO&& other) noexcept;
    ~VAO();

    void bind();
    static void unbind();
    
    void setVertexAttribute(int index, GLint numComponents, GLsizei stride, void* componentOffset = (void*)0);

private:
    GLuint mId;
};

#endif