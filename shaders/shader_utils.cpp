#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>  // Make sure you have GLEW initialized

// Function to load shader from file
std::string LoadShaderCode(const std::string& filepath) {
    std::ifstream shaderFile(filepath);
    if (!shaderFile.is_open()) {
        std::cerr << "Error: Could not open shader file: " << filepath << std::endl;
        return "";
    }
    
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

// Function to compile a shader
GLuint CompileShader(GLenum shaderType, const std::string& shaderCode) {
    GLuint shader = glCreateShader(shaderType);
    const char* code = shaderCode.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetShaderInfoLog(shader, logLength, &logLength, log);
        std::cerr << "Shader Compilation Failed: " << log << std::endl;
        delete[] log;
    }

    return shader;
}

// Function to create a shader program from vertex and fragment shaders
GLuint CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
    // Load the shader codes
    std::string vertexCode = LoadShaderCode(vertexPath);
    std::string fragmentCode = LoadShaderCode(fragmentPath);

    // Compile the shaders
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // Create the shader program and attach the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetProgramInfoLog(shaderProgram, logLength, &logLength, log);
        std::cerr << "Shader Program Linking Failed: " << log << std::endl;
        delete[] log;
    }

    // Clean up the shaders as they are no longer needed after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
