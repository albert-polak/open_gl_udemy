#pragma once

#include <GL/glew.h>
#include <glm.hpp>

class Light
{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);

    void useLight(GLint ambientIntensityLocation, GLint ambientColourLocation);
    ~Light();
private:
    glm::vec3 colour;
    GLfloat ambientIntensity;
};