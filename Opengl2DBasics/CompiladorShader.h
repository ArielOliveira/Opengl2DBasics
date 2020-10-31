#pragma once

#include <glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Constantes para índices de attributos no vertex shader
const unsigned VERTEX_SHADER_POSITION = 0;

// Constantes para formato do buffer
const unsigned VERTEX_BUFFER_SIZE = 2; // usaremos apenas x e y para representar os vértices

enum class ShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};



static ShaderProgramSource ParseShader(const std::string& filepath) {
	std::fstream stream(filepath);
	
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		} else {
			ss[int(type)] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

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