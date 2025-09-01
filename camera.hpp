#pragma once

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    Camera(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
    ~Camera();

    void keyControl(bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    glm::mat4 calculateViewMatrix();

private:
    glm::vec3 position, front, up, right, worldUp;

    GLfloat yaw, pitch;

    GLfloat movementSpeed;
    GLfloat turnSpeed;

    void update();
};