#include <glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Object.h"
#include "Square.h"
#include "Circle.h"
#include "CompiladorShader.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

int Object::instances = 0;

using glm::mat4;
using glm::translate;
using glm::vec3;

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


    ShaderProgramSource source = ParseShader("Shader.shader");
    unsigned shader = CriarShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    glBindAttribLocation(shader, VERTEX_SHADER_POSITION, "position");  // Associa um número a um atributo no vertex shader
    unsigned movimento = glGetUniformLocation(shader, "transform"); // Retorna o valor unsigned int de um uniform
   
    
    if (!shader)
        return -1;

    float verts[] = {
        -.5f, -.5f,
         .5f, -.5f,
         .5f,  .5f,
        -.5f,  .5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}