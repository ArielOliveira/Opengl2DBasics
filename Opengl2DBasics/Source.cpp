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


    ShaderProgramSource source = ParseShader("Shader.shader");
    unsigned shader = CriarShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    glBindAttribLocation(shader, VERTEX_SHADER_POSITION, "position");  // Associa um número a um atributo no vertex shader
    unsigned movimento = glGetUniformLocation(shader, "movimento"); // Retorna o valor unsigned int de um uniform
   
    
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

    Square *square = new Square(*indices, *verts, mat4(1.f), mat4(1.f), mat4(1.f), mat4(1.f));

    unsigned buffer;
    glGenBuffers(1, &buffer); // Gera um objeto de buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // Determina o tipo do objeto de buffer
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), verts, GL_STATIC_DRAW); // Determina o tipo, tamanho, ponteiro e padrao de armazenamento respectivamente
    
    glEnableVertexAttribArray(VERTEX_SHADER_POSITION); // Habilita o atributo a ser usado na chamada do metodo draw
    glVertexAttribPointer(VERTEX_SHADER_POSITION, VERTEX_BUFFER_SIZE, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // Define uma array a ser usada no attributo do vertex shader

    unsigned ibo;

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    mat4 move(1.f);
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        move = glm::translate(move, glm::vec3(.00001f, .0f, .0f));
        glUniformMatrix4fv(movimento, 1, GL_FALSE, glm::value_ptr(move));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}