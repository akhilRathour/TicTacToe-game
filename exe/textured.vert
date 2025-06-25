#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

layout (location = 1) in vec2 aTex; // the texture coordinate variable has attribute position 1
uniform float scale;
out vec3 ourColor; // output a color to the fragment shader
out vec2 TexCoord; // output texture coordinate to the fragment shader
void main()
{
    gl_Position = vec4(aPos, 1.0)*scale;
   
    TexCoord = aTex; // set ourTexCoord to the input texture coordinate we got from the vertex data
} 