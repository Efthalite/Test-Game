#include "Render.hpp"

#include <glad/glad.h>

unsigned int CreateQuadVAO(float size, unsigned int* getIndicesAmount)
{
    const unsigned int verticesAmount = 4,
    parametersPerVertex = 3,
    indicesAmount = 6;

    //*getIndicesAmount = indicesAmount;

    float *quadVertices = new float[verticesAmount * parametersPerVertex] 
    {
        -size, -size,  1.0f,
        -size,  size,  1.0f,
         size,  size,  1.0f,
         size, -size,  1.0f
    };

    unsigned int indexVertices[indicesAmount] = 
    {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int VAO, VBO, IBO;


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesAmount * parametersPerVertex * sizeof(float), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesAmount * sizeof(float), indexVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glDisableVertexAttribArray(0);


    delete[] quadVertices;

    return VAO;
}

void RenderQuad(unsigned int VAO)
{
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

}
