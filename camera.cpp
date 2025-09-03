#include "camera.hpp"

#include <GLFW/glfw3.h>

Camera::Camera()
{
}

Camera::Camera(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) :
    position(initialPosition), worldUp(initialUp), yaw(initialYaw), pitch(initialPitch), movementSpeed(startMoveSpeed), turnSpeed(startTurnSpeed)
{
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    update();
}

Camera::~Camera()
{
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
    GLfloat velocity = movementSpeed * deltaTime;
    glm::vec3 direction{0.0f, 0.0f, 0.0f};
    if (keys[GLFW_KEY_W])
    {
        direction += front;
        // position += front * velocity;
    }
    else if (keys[GLFW_KEY_S])
    {
        direction -= front;
        // position -= front * velocity;
    }
    if (keys[GLFW_KEY_A])
    {
        direction -= right;
        // position -= right * velocity;
    }
    else if (keys[GLFW_KEY_D])
    {
        direction += right;
        // position += right * velocity;
    }
    if (keys[GLFW_KEY_SPACE])
    {
        direction += worldUp;
        // position += up * velocity;
    }
    else if (keys[GLFW_KEY_LEFT_CONTROL])
    {
        direction -= worldUp;
        // position -= up * velocity;
    }
    if (glm::length(direction) > 0.0f)
        direction = glm::normalize(direction);

    position += direction * velocity;
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    update();
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
