#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Object.h"
#include "Square.h"
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

    Square *square = new Square(verts, indices, glm::mat4(1), mat4(1), mat4(1), mat4(1));

    //VertexBuffer vb(square->GetVertexArray(), square->GetIndexBufferSize());

    glGenBuffers(1, square->GetVertexPtr()); // Gera um objeto de buffer
    glBindBuffer(GL_ARRAY_BUFFER, square->GetVertexBufferID()); // Determina o tipo do objeto de buffer
    glBufferData(GL_ARRAY_BUFFER, square->GetVertexBufferSize(), square->GetVertexArray(), GL_STATIC_DRAW); // Determina o tipo, tamanho, ponteiro e padrao de armazenamento respectivamente
    
    glEnableVertexAttribArray(VERTEX_SHADER_POSITION); // Habilita o atributo a ser usado na chamada do metodo draw
    glVertexAttribPointer(VERTEX_SHADER_POSITION, VERTEX_BUFFER_SIZE, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // Define uma array a ser usada no attributo do vertex shader

    //unsigned ibo;

    glGenBuffers(1, square->GetIndexPtr());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square->GetIndexBufferID());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, square->GetIndexBufferSize() * sizeof(unsigned int), square->GetIndexArray(), GL_STATIC_DRAW);

    mat4 move(1);
    
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr);        
        square->Rotate(glm::vec2(.005f, .005f), vec3(.0f, .0f, 1));
        glUniformMatrix4fv(movimento, 1, GL_FALSE, glm::value_ptr(square->GetTransform()));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}