#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader();
    ~Shader();

    void createFromString(const char* vertexCode, const char* fragmentCode);
    void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

    std::string readFile(const char* fileLocation);

    GLuint getProjectionLocation();
    GLuint getModelLocation();

    void useShader();
    void clearShader();

private:
    GLuint shaderID, uniformProjection, uniformModel;

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};