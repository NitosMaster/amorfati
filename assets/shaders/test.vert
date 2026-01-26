#version 330 core

layout (location = 0) in vec3 aPos; 
out vec4 vertexColor; 

void main()
{
    gl_Position = vec4(aPos, 1.0); 
    vertexColor = vec4(120.0/255.0, 150.0/255.0, 30.0/255.0, 1.0); 
}
