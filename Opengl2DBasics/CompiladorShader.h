#pragma once

#include <glew.h>
#include <iostream>
#include <string>

// Constantes para índices de attributos no vertex shader
const unsigned VERTEX_SHADER_POSITION = 0;

// Constantes para formato do buffer
const unsigned VERTEX_BUFFER_SIZE = 2; // usaremos apenas x e y para representar os vértices

std::string vertexShader =
	"#version 330 core\n"
	"\n"
	"in vec4 position;"
	"\n"
	"uniform mat4 modelo"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = position * modelo;\n"
	"}\n";

std::string fragmentShader =
	"#version 330 core\n"
	"\n"
	"out vec4 color;"
	"\n"
	"void main()\n"
	"{\n"
"		color = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n";

static unsigned CompilarShader(unsigned type, const std::string& source) {
	unsigned id = glCreateShader(type); // Cria um objeto shader e atribui seu valor ao id
	const char* src = source.c_str(); 
	glShaderSource(id, 1, &src, nullptr); // Carrega a string para ser código fonte do shader especificado
	glCompileShader(id); // Compila o shader

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result); 
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "O Shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<  " falhou ao compilar! " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static unsigned CriarShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned program = glCreateProgram(); // Cria um objeto de programa
	unsigned vs = CompilarShader(GL_VERTEX_SHADER, vertexShader);
	unsigned fs = CompilarShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs); // Liga o shader compilado ao objeto de programa
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}