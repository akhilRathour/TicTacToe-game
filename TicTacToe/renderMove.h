#ifndef renderMove_H
#define renderMove_H

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "EBO.h"	
// Renders a textured quad in a given cell index (0–8)
// If isX == true, use texture1 (e.g., "X"); else use texture2 (e.g., "O")
void draw_cell(int cellIndex, bool isX, Shader& shader, Texture& textureX, Texture& textureO);

#endif
