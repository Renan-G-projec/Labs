// Ad Maiorem Dei Gloriam!
#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>
#include <glad/gl.h>
#include <glm/mat4x4.hpp>

class Shader 
{
public:
    Shader();
    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    ~Shader();

    void activate() const;
    static void deactivate();

    void attachFile(const std::string& file, GLenum type) const;
    void link();

    void setUniformMatrix(const glm::mat4& matrix, const char *uniform = "uMVP");
    void setUniformSampler2D(const GLint sampler2d, const char* uniform = "uTex");
    void setUniformInt(const GLint intval, const char *uniform);
    void setUniformFloat(const GLfloat floatval, const char* uniform);
    void setUniformVec3(const glm::vec3 vec, const char *uniform);
    void setUniformVec2(const glm::vec2 vec, const char* uniform);
    void setUniformIVec2(const glm::ivec2 vec, const char *uniform);

    GLuint getUniformLocation(const char *uniform);

private:
    GLuint mId;
    std::unordered_map<const char *, GLuint> mUniformsLocation;

};

#endif