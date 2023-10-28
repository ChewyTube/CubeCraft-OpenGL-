#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "../enum.h"

namespace cubecraft {
	class Shader {
	public:
		const GLchar* readFromFile(const GLchar* path);
		void compileShaders(const GLchar* shaderSource, ShaderType type);
		void createShaderProgram();
		void Use();
	private:
		GLuint shaderProgram;

		GLint success;
		GLchar infoLog[512];

		std::vector<GLuint> vertexShaders;
		std::vector<GLuint> geometryShaders;
		std::vector<GLuint> fragmentShaders;
	};
}
