#include "gl_window.hpp"

Window::Window()
{
    width = 800;
    height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
    : width(windowWidth),
      height(windowHeight)
{
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

int Window::initialize()
{
    // init glfw
    if (!glfwInit())
    {
        printf("GLFW initialization failed...");
        glfwTerminate();
        return 1;
    }

    // setup window properties
    // opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, "myapp", nullptr, nullptr);

    if (!mainWindow)
    {
        printf("GLFW error creating window...");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW init error...");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, bufferWidth, bufferHeight);
}