#include <iostream>
#include <cstring>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <vector>

#include "gl_window.hpp"
#include "mesh.hpp"
#include "shader.hpp"

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

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
static const char* vShader = "shaders/shader.vert";

static const char* fShader = "shaders/shader.frag";

void createObjects()
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

    Mesh* obj1 = new Mesh();
    Mesh* obj2 = new Mesh();
    obj1->createMesh(vertices, indices, 12, 12);
    obj1->createMesh(vertices, indices, 12, 12);
    obj2->createMesh(vertices, indices, 12, 12);
    obj2->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);
    meshList.push_back(obj2);
}

void createShaders()
{
    Shader *shader1 = new Shader();
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(shader1);
}

int main()
{
    auto mainWindow = Window(WIDTH, HEIGHT);
    mainWindow.initialize();

    createObjects();
    createShaders();

    GLuint uniformProjection = 0, uniformModel = 0;

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth()/(GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    while (!mainWindow.getShouldClose())
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

        for (auto shader : shaderList)
        {
            shader->useShader();
            uniformModel = shader->getModelLocation();
            uniformProjection = shader->getProjectionLocation();

            glm::mat4 model(1.0);
            model = glm::translate(model, {0.0, triOffset, -2.5f});
            model = glm::rotate(model, curAngle * toRadians, {0, 1.0, 0});
            model = glm::scale(model, {0.4, 0.4, 0.4});

            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            meshList[0]->renderMesh();

            model = glm::mat4(1.0);
            model = glm::translate(model, {-0.5, triOffset, -2.5f});
            model = glm::rotate(model, curAngle * toRadians, {0, 1.0, 0});
            model = glm::scale(model, {0.4, 0.4, 0.4});

            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

            meshList[1]->renderMesh();
        }

        // for (auto mesh : meshList)
        // {
        // }

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}