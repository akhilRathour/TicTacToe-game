#ifndef GRID_H
#define GRID_H

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

// Vertex data for a 3x3 grid (4 vertical + 4 horizontal lines)
extern float gridVertices[32];  // 16 (x, y) vertex pairs = 32 floats

// Function to draw the grid using OpenGL
void draw_grid(Shader& shaderProgram, VAO& gridVAO);

// Function to set up VAO and VBO for the grid
void setup_grid(VAO& gridVAO, VBO& gridVBO);

#endif
