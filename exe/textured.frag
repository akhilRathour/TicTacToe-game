#version 330 core
out vec4 FragColor;  in vec3 ourColor; //from pipeline
in vec2 TexCoord; //from pipeline
uniform sampler2D tex0; //texture unit 0

void main()
{
   FragColor = texture(tex0,TexCoord);
   //FragColor = vec4(1.0, 0.0, 0.0, 1.0); 

}