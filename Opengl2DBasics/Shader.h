#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
	private:
		std::string filePath;
		std::unordered_map<std::string, int> uniformLocationCache;
		unsigned int rendererID;
		unsigned int CompileShader(unsigned type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgramSource ParseShader(const std::string& filepath);
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind();
		void Unbind();

		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMatrix4fv(const std::string& name, const float* matrix);

		unsigned int GetUniformLocation(const std::string& name);
		unsigned int GetID() { return rendererID; }
};

