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

    void swapBuffers() { glfwSwapBuffers(mainWindow); }

private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;
};