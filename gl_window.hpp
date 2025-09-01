#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    ~Window();

    int initialize();

    GLint getBufferWidth() const { return bufferWidth; }
    void setBufferWidth(const GLint &bufferWidth_) { bufferWidth = bufferWidth_; }

    GLint getBufferHeight() const { return bufferHeight; }
    void setBufferHeight(const GLint &bufferHeight_) { bufferHeight = bufferHeight_; }

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    bool* getKeys() { return keys; }
    GLfloat getXChange();
    GLfloat getYChange();


    void swapBuffers() { glfwSwapBuffers(mainWindow); }

private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    double lastX, lastY, xChange, yChange = 0.0f;
    bool mouseFirstMoved = true;

    void createCallbacks();

    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};