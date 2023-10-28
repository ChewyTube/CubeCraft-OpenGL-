#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "../Shader/Shader.h"
#include "../enum.h"

namespace cubecraft {
	class Renderer {
	public:
		static Renderer* Instance();

		void Init();
		void Loop();
		void Quit();
	private:
		Renderer();
		~Renderer();
		void createVBO();
		void createVAO();
		void createEBO();
		void compileShaders(GLuint &shader, const GLchar* shaderSource, ShaderType type);
		void createShaderProgram(std::vector<GLuint> shaders);

		static Renderer* p_Renderer;
		GLFWwindow* window;
		GLuint VBO, VAO, EBO;//缓冲ID
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;

		GLint success;
		GLchar infoLog[512];

		Shader shader;

		GLfloat vertices[12] = {
			 0.5f,  0.5f, 0.0f,   // 右上角
			 0.5f, -0.5f, 0.0f,  // 右下角
			-0.5f, -0.5f, 0.0f, // 左下角
			-0.5f,  0.5f, 0.0f   // 左上角
		};

		GLuint indices[6] = {
			0, 1, 3, // 第一个三角形
			1, 2, 3  // 第二个三角形
		};
		const GLchar* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"}\0";
		const GLchar* fragmentShaderSource = "#version 330 core\n"
			"out vec4 color;\n"
			"void main()\n"
			"{\n"
			"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
		
	};
}
