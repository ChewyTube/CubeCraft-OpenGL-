#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace cubecraft {
	class Shader {
	public:
		// ≥Ã–ÚID
		GLuint Program;

		void readAndCompileShaders(const GLchar* vertPath, const GLchar* fragPath);
		void Use();
	private:
	};
}