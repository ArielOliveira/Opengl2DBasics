#include <glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "DiceFace.h"
#include "Camera.h"
#include "Shader.h"

int Object::instances = 0;

using glm::mat4;
using glm::translate;
using glm::vec2;
using glm::vec3;
using glm::vec4;

vector<DiceFace*>* dice;
Camera* camera;
Camera* cameraDolly;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    vec4 facePos;
    vec4 cameraPos;
    vec4 travelDistance;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        camera->Translate(vec3(.5f, .0f, .0f));
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        camera->Translate(vec3(.0f, .5f, .0f));
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        camera->Reset();
        cameraDolly->Reset();
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        facePos = dice->at(0)->GetPosition() * vec4(0, 0, 0, 1);
        cameraPos = camera->GetPosition() * vec4(0, 0, 0, 1);

        travelDistance = (facePos * -1.f) - cameraPos;

        camera->Translate(vec3(travelDistance.x, travelDistance.y, .0f));
        cameraDolly->Scale(vec3(1.2f, 1.2f, 1));
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        facePos = (*dice)[5]->GetPosition() * vec4(0, 0, 0, 1);
        cameraPos = camera->GetPosition() * vec4(0, 0, 0, 1);

        travelDistance = (facePos * -1.f) - cameraPos;

        camera->Translate(vec3(travelDistance.x, travelDistance.y, .0f));
        cameraDolly->Scale(vec3(.5f, .5f, 1));
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        facePos = (*dice)[0]->GetPosition() * camera->GetScale() * vec4(0, 0, 0, 1);
        cameraPos = camera->GetPosition() * vec4(0, 0, 0, 1);

        travelDistance = (facePos * -1.f) - cameraPos;
        glm::normalize(travelDistance);

        camera->Translate(vec3(travelDistance.x, travelDistance.y, .0f));
        cameraDolly->Rotate(vec2(0.f, 45.f), vec3(0, 0, 1));
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        vector<DiceFace*>::iterator it = dice->begin();
        (*++it)->Translate(vec3(.5f, 0, 0));
        (*++it)->Translate(vec3(0, .5f, 0));
        (*++it)->Translate(vec3(0, -.5f, 0));
        (*++it)->Translate(vec3(-.5f, 0, 0));
        (*++it)->Translate(vec3(-.5f, 0, 0));
    }
}

int main(void) 
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;

    Shader* shader = new Shader("Shader.shader");
    shader->Bind();

    GLCall(glBindAttribLocation(shader->GetID(), VERTEX_SHADER_POSITION, "position"));  // Associa um número a um atributo no vertex shader

    dice = new vector<DiceFace*>();
    dice->push_back(new DiceFace(1, mat4(1), mat4(1), mat4(1)));
    dice->push_back(new DiceFace(2, translate(mat4(1), vec3(1, .0f, .0f)), mat4(1), mat4(1)));
    dice->push_back(new DiceFace(3, translate(mat4(1), vec3(.0, 1, .0f)), mat4(1), mat4(1)));
    dice->push_back(new DiceFace(4, translate(mat4(1), vec3(.0, -1, .0f)), mat4(1), mat4(1)));
    dice->push_back(new DiceFace(5, translate(mat4(1), vec3(-1, 0, .0f)), mat4(1), mat4(1)));
    dice->push_back(new DiceFace(6, translate(mat4(1), vec3(-2, 0, .0f)), mat4(1), mat4(1)));

    camera = new Camera(translate(mat4(1), vec3(.5f, .0f, .0f)), mat4(1), mat4(1));
    shader->SetUniformMatrix4fv("camera", &camera->GetTransform());
    cameraDolly = new Camera(mat4(1), mat4(1), scale(mat4(1), vec3(.5f, .5f, 1)));
    shader->SetUniformMatrix4fv("cameraParent", &cameraDolly->GetTransform());
    
    for (auto& diceFace : *dice)
        shader->SetUniformMatrix4fv("transform", (&(diceFace)->GetTransform()));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //Entrada/Input
        glfwSetKeyCallback(window, key_callback);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        cameraDolly->Draw(shader->GetUniformLocation("cameraParent"));
        camera->Draw(shader->GetUniformLocation("camera"));
        for (auto& diceFace : *dice) {
            (diceFace)->Bind();
            (diceFace)->Draw(shader->GetUniformLocation("transform"));
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    std::cout << Object::instances << std::endl;
    for (auto& diceFace : *dice)
        delete diceFace;

    delete dice;
    delete camera;
    delete cameraDolly;

    std::cout << Object::instances << std::endl;
    shader->Unbind();
    delete shader;
    glfwTerminate();
    return 0;
}