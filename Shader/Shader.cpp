#include "Shader.h"

namespace cubecraft {
    const GLchar* Shader::readFromFile(const GLchar* path) {
        // 1. 从文件路径中获取顶点/片段着色器
        std::string code;
        std::ifstream shaderFile;
        // 保证ifstream对象可以抛出异常：
        shaderFile.exceptions(std::ifstream::badbit);
        try
        {
            // 打开文件
            shaderFile.open(path);
            std::stringstream shaderStream;
            // 读取文件的缓冲内容到流中
            shaderStream << shaderFile.rdbuf();
            // 关闭文件
            shaderFile.close();
            // 转换流至GLchar数组
            code = shaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* shaderCode = code.c_str();

        return shaderCode;
    }

    void Shader::compileShaders(const GLchar* shaderSource, ShaderType type) {
        GLuint shader;
        //创建
        switch (type)
        {
        case cubecraft::vertex:
            shader = glCreateShader(GL_VERTEX_SHADER);
            vertexShaders.push_back(shader);
            break;
        case cubecraft::geometry:
            shader = glCreateShader(GL_GEOMETRY_SHADER);
            geometryShaders.push_back(shader);
            break;
        case cubecraft::fragment:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            fragmentShaders.push_back(shader);
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

    void Shader::createShaderProgram() {
        //合并
        std::vector<GLuint> shaders = vertexShaders;
        shaders.insert(shaders.end(), geometryShaders.begin(), geometryShaders.end());
        shaders.insert(shaders.end(), fragmentShaders.begin(), fragmentShaders.end());
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

    void Shader::Use() {
        glUseProgram(this->shaderProgram);
    }
}

