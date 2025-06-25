#include <glad/glad.h>
#include "shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"grid.h"
float gridVertices[] = {
	// Vertical lines (x fixed, y from -1 to 1)
   -1.0f, -1.0f,  -1.0f,  1.0f,  // left edge
   -0.333f, -1.0f, -0.333f, 1.0f,
	0.333f, -1.0f,  0.333f, 1.0f,
	1.0f, -1.0f,   1.0f,   1.0f,  // right edge

	// Horizontal lines (y fixed, x from -1 to 1)
   -1.0f, -1.0f,   1.0f, -1.0f,  // bottom edge
   -1.0f, -0.333f, 1.0f, -0.333f,
   -1.0f,  0.333f, 1.0f,  0.333f,
   -1.0f,  1.0f,   1.0f,  1.0f   // top edge
};

void setup_grid(VAO& gridVAO, VBO& gridVBO) {
	gridVAO.Bind();
	gridVBO = VBO(gridVertices, sizeof(gridVertices));

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	gridVAO.Unbind();
	gridVBO.Unbind();
}

void draw_grid(Shader& shaderProgram, VAO& gridVAO) {
	shaderProgram.Activate();
	gridVAO.Bind();
	glDrawArrays(GL_LINES, 0, 16);  // 8 lines * 2 points each = 16 vertices
	gridVAO.Unbind();
}