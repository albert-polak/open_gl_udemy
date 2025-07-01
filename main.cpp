#include <iostream>
#include <cstring>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

GLuint VAO, VBO, IBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 1.0f;
float triIncrement = 0.0005f;

float curAngle = 0.0f;
float angleIncrement = 0.01f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 1.0f;
float minSize = 0.1f;
float scaleIncrement = 0.001f;


// vertex shader
static const char* vShader = R"VOGON(
#version 330

layout (location = 0) in vec3 pos;

out vec4 vCol;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(pos.x, pos.y, pos.z, 1.0);
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}
)VOGON";

static const char* fShader = R"VOGON(
#version 330

in vec4 vCol;

out vec4 colour;

void main()
{
    colour = vCol;
}
)VOGON";

void createTriangle()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = static_cast<GLint>(strlen(shaderCode));

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("error compile %d shader %s\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}

void compileShaders() 
{
    shader = glCreateProgram();

    if (!shader)
    {
        printf("Error creating shader program!\n");
        return;
    }

    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("error linking program %s\n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("error validating program %s\n", eLog);
        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");
}

int main()
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

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "myapp", nullptr, nullptr);

    if (!mainWindow)
    {
        printf("GLFW error creating window...");
        glfwTerminate();
        return 1;
    }

    int bufferHeight, bufferWidth;
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

    createTriangle();
    compileShaders();

    while (!glfwWindowShouldClose(mainWindow))
    {
        // user inputs
        glfwPollEvents();

        if (direction)
        {
            triOffset += triIncrement;
        }
        else
        {
            triOffset -= triIncrement;
        }

        if(abs(triOffset) >=  triMaxOffset)
        {
            direction = !direction;
        }

        if (sizeDirection)
        {
            curSize += scaleIncrement;
        }
        else
        {
            curSize -= scaleIncrement;
        }

        if (curSize >= maxSize || curSize <= minSize)
        {
            sizeDirection = !sizeDirection;
        } 

        curAngle += angleIncrement;
        if (curAngle >= 360)
        {
            curAngle = 0;
        }

        // clear window
        glClearColor(0.0f,0.5f,0.5f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        glm::mat4 model(1.0);
        // model = glm::translate(model, {triOffset, 0.0f, 0.0f});
        model = glm::rotate(model, curAngle * toRadians, {0, 1.0, 0});
        model = glm::scale(model, {0.4, 0.4, 0.4});

        // glUniform1f(uniformModel, triOffset);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}