#include "Renderer.h"

#include <assert.h>
#include <iostream>

namespace cubecraft {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

	Renderer* Renderer::p_Renderer = new Renderer();
    

	Renderer::Renderer() {
        ;
	}
	Renderer::~Renderer() {
		;
	}

	Renderer* Renderer::Instance() {
		assert(p_Renderer);
		return p_Renderer;
	}
	void Renderer::Init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        //窗口对象
        window = glfwCreateWindow(800, 600, "CubeCraft", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            Quit();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, cubecraft::framebuffer_size_callback);

        //初始化GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            Quit();
        }

        glViewport(0, 0, 800, 600);
        /*
        compileShaders(vertexShader, vertexShaderSource, ShaderType::vertex);
        compileShaders(fragmentShader, fragmentShaderSource, ShaderType::fragment);
        createShaderProgram({vertexShader, fragmentShader});
        */
        
        createVAO();
        shader.readAndCompileShaders("Shader/shader.vert", "Shader/shader.frag");
        glBindVertexArray(VAO);
        createVBO();
        createEBO();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        //shader.compileShaders(shader.readFromFile("Shader/shader.vert"), ShaderType::vertex);
        //shader.compileShaders(shader.readFromFile("Shader/shader.frag"), ShaderType::fragment);
        //shader.createShaderProgram();
        //shader.readAndCompileShader("Shader/shader.vert", "Shader/shader.frag");
	}
    void Renderer::Loop() {
        //渲染循环
        while (!glfwWindowShouldClose(window))
        {
            // 输入
            processInput(window);

            // 渲染指令
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Use();
            glBindVertexArray(VAO); 
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // 检查并调用事件，交换缓冲
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }
	void Renderer::Quit() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glfwTerminate();
	}

    void Renderer::createVAO() {
        glGenVertexArrays(1, &VAO);//创建
    }
    void Renderer::createVBO() {
        glGenBuffers(1, &VBO);//创建

        glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓冲
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//复制数据
    }
    void Renderer::createEBO() {
        //创建
        glGenBuffers(1, &EBO);
        //绑定数据
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    /*
    void Renderer::compileShaders(GLuint& shader, const GLchar* shaderSource, ShaderType type) {
        //创建
        switch (type)
        {
        case cubecraft::vertex:
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case cubecraft::geometry:
            shader = glCreateShader(GL_GEOMETRY_SHADER);
            break;
        case cubecraft::fragment:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            throw "undefined type";
            break;
        }
        //编译
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        //验证
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    */
    /*
    void Renderer::createShaderProgram(std::vector<GLuint> shaders) {
        shaderProgram = glCreateProgram();
        //绑定
        for (auto shader : shaders) {
            glAttachShader(shaderProgram, shader);
        }
        //链接
        glLinkProgram(shaderProgram);
        //验证
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        //删除多余文件
        for (auto shader : shaders) {
            glDeleteShader(shader);
        }
    }
    */
}