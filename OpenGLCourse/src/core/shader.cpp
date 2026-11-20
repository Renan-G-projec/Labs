// Ad Maiorem Dei Gloriam!

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>
#include <string>

#include "core/shader.hpp"
#include "core/log.hpp"

Shader::Shader() 
{
    mId = glCreateProgram();
}

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
    mId = glCreateProgram();
    attachFile(vertexFile, GL_VERTEX_SHADER);
    attachFile(fragmentFile, GL_FRAGMENT_SHADER);
    link();
}

Shader::~Shader()
{
    glDeleteProgram(mId);
}

void Shader::attachFile(const std::string& file, GLenum type) const
{
    GLuint shader = glCreateShader(type);
    std::string src;
    std::ifstream fileStream{file};
    if (!fileStream.is_open())
    {
        Log::log_error("Error: Could not open file " + file + " while trying to attach shader.");
        return;
    }

    std::getline(fileStream, src, '\0');
    const char *srcString = src.c_str();

    glShaderSource(shader, 1, &srcString, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLsizei logSize;
        char log[512];
        glGetShaderInfoLog(shader, sizeof(log), &logSize, log);
        Log::log_error("Could not compile shader " + file + '\n' + std::string(log));

        return;
    }

    Log::log_debug("Success on loading and compiling " + file + " shader!");

    glAttachShader(mId, shader);
    glDeleteShader(shader);
}

void Shader::link() 
{
    glLinkProgram(mId);
    int success;
    glGetProgramiv(mId, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLsizei logSize;
        char log[512];
        glGetProgramInfoLog(mId, sizeof(log), &logSize, log);

        Log::log_error("Error while linking shader\n" + std::string(log));
        return;
    }
}

void Shader::activate() const 
{
    glUseProgram(mId);
}

void Shader::deactivate() {
    glUseProgram(0);
}

void Shader::setUniformMatrix(const glm::mat4& matrix, const char* uniform) 
{
    const GLuint location = getUniformLocation(uniform);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformSampler2D(const GLint sampler2D, const char* uniform)
{
    setUniformInt(sampler2D, uniform);
}

void Shader::setUniformInt(const GLint intval, const char* uniform)
{
    const GLuint location = getUniformLocation(uniform);
    glUniform1i(location, intval);
}

void Shader::setUniformFloat(const GLfloat floatval, const char* uniform)
{
    const GLuint location = getUniformLocation(uniform);
    glUniform1f(location, floatval);
}

void Shader::setUniformVec3(const glm::vec3 vec, const char* uniform)
{
    const GLuint location = getUniformLocation(uniform);
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setUniformVec2(const glm::vec2 vec, const char* uniform)
{
    const GLuint location = getUniformLocation(uniform);
    glUniform2f(location, vec.x, vec.y);
}

void Shader::setUniformIVec2(const glm::ivec2 vec, const char* uniform)
{
    const GLuint location = getUniformLocation(uniform);
    glUniform2i(location, vec.x, vec.y);
}

GLuint Shader::getUniformLocation(const char *uniform) 
{
    if (mUniformsLocation.find(uniform) == mUniformsLocation.end()) 
    {
        mUniformsLocation.insert({uniform, glGetUniformLocation(mId, uniform)});
    }
    return mUniformsLocation.at(uniform);
}