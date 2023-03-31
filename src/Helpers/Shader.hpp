#pragma once

#include <string>


std::string GetFileContents(std::string filePath);
unsigned int CreateShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);