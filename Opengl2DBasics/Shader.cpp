#include "Shader.h"
#include "OpenglDebugger.h"
#include <glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum class ShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

Shader::Shader(const std::string& filepath) : filePath(filepath), rendererID(0) {
	ShaderProgramSource source = ParseShader(filepath);
	rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(rendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
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
		}
		else {
			ss[int(type)] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned type, const std::string& source) {
	unsigned id = glCreateShader(type); // Cria um objeto shader e atribui seu valor ao id
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr); // Carrega a string para ser código fonte do shader especificado
	glCompileShader(id); // Compila o shader

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "O Shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " falhou ao compilar! " << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram(); // Cria um objeto de programa
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs)); // Liga o shader compilado ao objeto de programa
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void Shader::Bind() const { GLCall(glUseProgram(rendererID)) }
void Shader::Unbind() const { GLCall(glUseProgram(0)); }

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(SetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMatrix4fv(const std::string& name, const float* matrix) {
	GLCall(glUniformMatrix4fv(SetUniformLocation(name), 1, GL_FALSE, matrix));
}

int Shader::SetUniformLocation(const std::string& name) {
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));
	if (location == -1)
		std::cout << "warning: uniform '" << name << "' doesn't exist!" << std::endl;
	uniformLocationCache[name] = location;
	return location;
}

const int Shader::GetUniformLocation(const std::string& name) const {
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache.at(name);
	else return -1;
}
