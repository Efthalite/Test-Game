#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Helpers/Shader.hpp"
#include "Helpers/Render.hpp"



void ProcessInput(GLFWwindow*);

const unsigned int width = 900, height = 900;


int main()
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    //glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Game", nullptr, nullptr);

    if(!window)
    {
        std::cerr << "Failed to create a window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize OpenGL function loaders\n";
        glfwTerminate();        
        return -1;
    }

    glViewport(0, 0, width, height);

    glfwShowWindow(window);


    unsigned int shaderProgram = CreateShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    unsigned int quadVAO = CreateQuadVAO((float)1/4, nullptr);

    unsigned int* map = new unsigned int[2*2]
    {
        0, 0,
        1, 1
    };



    // Main Loop

    while (!glfwWindowShouldClose(window))
    {
        // Input
        glfwPollEvents();
        ProcessInput(window);



        // Render

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3f, 1.0f, 0.3f, 1.0f);


        glUseProgram(shaderProgram);

        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                if(map[i*2 + j] == 1)
                {

                    glm::vec4 change = glm::vec4((float)i/4, (float)j/4, 0.0f, 0.0f);
                    glUniform4f(glGetUniformLocation(shaderProgram, "Change"), change.x, change.y, change.z, change.y);
                    RenderQuad(quadVAO);
                }

            }
        }



        

        glUseProgram(0);


        glfwSwapBuffers(window);
    }
    


    // Free everything

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}




void ProcessInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}






        // for(int i = 0; i < 2; i++)
        // {
        //     for(int j = 0; j < 2; j++)
        //     {
        //         if(map[i*2 + j] == 1)
        //         {

        //             glm::vec4 change = glm::vec4((float)i/4, (float)j/4, 1.0f, 0.0f);
        //             glUniform4f(glGetUniformLocation(shaderProgram, "Change"), change.x, change.y, change.z, change.y);
        //             RenderQuad(quadVAO);
        //         }

        //     }
        // }