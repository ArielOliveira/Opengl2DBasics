#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Object.h"
#include "Square.h"
#include "CompiladorShader.h"

int Object::instances = 0;

using glm::mat4;
using glm::translate;
using glm::vec3;

mat4 matriz;

float translation[] = {   1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f, };

float positions[6] = {
        -.5f, -.5f,
         .0f,  .5f,
         .5f, -.5f
};

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

    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;

    unsigned shader = CriarShader(vertexShader, fragmentShader);
    
    if (!shader)
        return -1;

    // Associa um número a um atributo no vertex shader
    glBindAttribLocation(shader, VERTEX_SHADER_POSITION, "position");
    unsigned movimento = glGetUniformLocation(shader, "modelo");

    glUseProgram(shader);

    float verts[8] = {
        -.5f, -.5f,
         .5f, -.5f,
         .5f,  .5f,
        -.5f,  .5f
    };

    Square *square = new Square(*verts, mat4(1.f), mat4(1.f), mat4(1.f), mat4(1.f));

    unsigned buffer;
    // Gera um objeto de buffer
    glGenBuffers(1, &buffer);

    // Determina o tipo do objeto de buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Determina o tipo, tamanho, ponteiro e padrao de armazenamento respectivamente
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Determina o tipo do objeto de buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        // Habilita o atributo a ser usado na chamada do metodo draw
        glEnableVertexAttribArray(VERTEX_SHADER_POSITION);

        // Define uma array a ser usada no attributo do vertex shader
        glVertexAttribPointer(VERTEX_SHADER_POSITION, VERTEX_BUFFER_SIZE, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        translation[3] += 0.2f;
        glUniformMatrix4fv(movimento, 1, GL_FALSE, translation);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}