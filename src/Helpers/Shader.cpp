#include "Shader.hpp"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

std::string GetFileContents(std::string filePath)
{
    std::string resultString;
    std::stringstream bufferStream;
    std::ifstream inFile;

    

    inFile.open(filePath.c_str(), std::ios::binary);

    if(!inFile)
    {
        std::cerr << "Could not find " << filePath << "\n";
    }

    bufferStream << inFile.rdbuf();

    resultString = bufferStream.str();

    return resultString;
}

unsigned int CreateShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    const std::string bufferVertexContainer = GetFileContents(vertexShaderPath);
    const std::string bufferFragmentContainer = GetFileContents(fragmentShaderPath);

    const char* vertexShaderSource = bufferVertexContainer.c_str();
    const char* fragmentShaderSource = bufferFragmentContainer.c_str();

    unsigned int shaderProgram = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const unsigned int logBufferSize = 2048;

    char errorLog[logBufferSize];
    int success;

    
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);



    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, logBufferSize, NULL, errorLog);

        std::cout << "Failed to compile Vertex Shader\n" << errorLog << "\n";
        return 0;
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, logBufferSize, NULL, errorLog);

        std::cout << "Failed to compile Fragment Shader\n" << errorLog << "\n";
        return 0;
    }


    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, logBufferSize, NULL, errorLog);

        std::cout << "Failed to Link Shaders\n" << errorLog << "\n";
        return 0;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    return shaderProgram;
}
