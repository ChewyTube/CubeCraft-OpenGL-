/*
#include "Shader.h"

namespace cubecraft {
    Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
    {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try
        {
            // Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        // 2. Compile shaders
        // Vertex Shader
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vShaderCode, NULL);
        glCompileShader(vs);
        // Print compile errors if any
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Fragment Shader
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fShaderCode, NULL);
        glCompileShader(fs);
        // Print compile errors if any
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Shader Program
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vs);
        glAttachShader(this->Program, fs);
        glLinkProgram(this->Program);
        // Print linking errors if any
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vs);
        glDeleteShader(fs);

    }

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
        //std::cout << shaderCode << std::endl;
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
        glShaderSource(shader, 0, &shaderSource, NULL);
        glCompileShader(shader);
        //验证
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    void Shader::readAndCompileShader(const GLchar* vertpath, const GLchar* fragpath) {
        const GLchar* vertCode = readFromFile(vertpath);
        const GLchar* fragCode = readFromFile(fragpath);
        // Vertex Shader
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertCode, NULL);
        glCompileShader(vs);
        // Print compile errors if any
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Fragment Shader
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragCode, NULL);
        glCompileShader(fs);
        // Print compile errors if any
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Shader Program
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        // Print linking errors if any
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void Shader::createShaderProgram() {
        //合并
        std::vector<GLuint> shaders = vertexShaders;
        shaders.insert(shaders.end(), geometryShaders.begin(), geometryShaders.end());
        shaders.insert(shaders.end(), fragmentShaders.begin(), fragmentShaders.end());
        Program = glCreateProgram();
        //绑定
        for (auto shader : shaders) {
            glAttachShader(Program, shader);
        }
        //链接
        glLinkProgram(Program);
        //验证
        glGetProgramiv(Program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        //删除多余文件
        for (auto shader : shaders) {
            glDeleteShader(shader);
        }
    }

    void Shader::Use() {
        glUseProgram(this->Program);
    }
}
*/
#include "Shader.h"

namespace cubecraft {
    void Shader::readAndCompileShaders(const GLchar* vertexPath, const GLchar* fragmentPath) {
        // 1. 从文件路径中获取顶点/片段着色器
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // 保证ifstream对象可以抛出异常：
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try
        {
            // 打开文件
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // 读取文件的缓冲内容到流中
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // 关闭文件
            vShaderFile.close();
            fShaderFile.close();
            // 转换流至GLchar数组
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        //--------------------------------------------------------------
        // 2. 编译着色器
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        // 顶点着色器
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // 打印编译错误（如果有的话）
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        // 片段着色器也类似
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // 打印编译错误（如果有的话）
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        // 着色器程序
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        // 打印连接错误（如果有的话）
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    
    void Shader::Use() {
        glUseProgram(this->Program);
    }
}

