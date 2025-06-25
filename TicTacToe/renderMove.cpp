#include "renderMove.h"

#include <vector>

// 3x3 grid layout
const int GRID_COLS = 3;
const int GRID_ROWS = 3;

// Each cell is 2.0 / 3.0 units wide in NDC
const float CELL_SIZE = 2.0f / 3.0f;

void draw_cell(int cellIndex, bool isX, Shader& shader, Texture& textureX, Texture& textureO)
{
    int row = cellIndex / GRID_COLS;
    int col = cellIndex % GRID_COLS;

    // Top-left of cell in NDC
    float x0 = -1.0f + col * CELL_SIZE;
    float y0 = 1.0f - row * CELL_SIZE;

    float x1 = x0 + CELL_SIZE;
    float y1 = y0 - CELL_SIZE;

    // Quad vertices (x, y, u, v)
    float quadVertices[] = {
        x0, y1, 0.0f, 0.0f, // bottom-left
        x1, y1, 1.0f, 0.0f, // bottom-right
        x1, y0, 1.0f, 1.0f, // top-right
        x0, y0, 0.0f, 1.0f  // top-left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VAO vao;
    vao.Bind();

    VBO vbo(quadVertices, sizeof(quadVertices));
    EBO ebo(indices, sizeof(indices));

    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // TexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Choose texture
    Texture& tex = isX ? textureX : textureO;
    tex.Bind(GL_TEXTURE0);

    shader.Activate();
	// Set uniform for scale
	int location = glGetUniformLocation(shader.ID, "scale");
    glUniform1f(location, 0.5);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}