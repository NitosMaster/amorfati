# this is just to keep track of concepts

## goal
I'm not sure exactly how high level I want this game engine to be but I'd like to make me never have to touch .vert, .frag and openGL funcs. Additionally I believe the scripting lang is going to be customizable and that means I'll have to do some .so/.ddl magic I'm going to delay as much as I can. As I want the engine to be fully customizable I plan on adding a config file the user can edit, to change certain core characteristics of the engine to their hearts desire. This config will be declaritive like NixOS.
## Whats a graphics API?
It talks to RAM and it essentially makes windows and draws pixels on those windows. It also renders stuff in 3D, such as vertices, edges and faces. For openGL to do that, I must give it a "Shader", that tells openGL where to put vertices and what color they should be. Shaders are seperate files written in GSLS, which kinda makes me wanna kys(kiss your sister). 

## Window
I have the amorfati::Window func to init a window, where background color can be set through rgba. It was actually kinda chill to do.

## WTF IS GSLS AND VBO AND FRAGMENTSHADER AND ETC...
GLSL is the lang that vertex(where are the points) and fragment shaders(what color) use. Here is how shaders tipically look:
``` cpp
#version 330 core // version

layout (location = 0) in vec3 aPos; // position
out vec4 vertexColor; // var with color, which you can also add in .vert and use in .frag later

void main() {
    gl_Position = vec4(aPos, 1.0); 
    vertexColor = vec4(120.0/255.0, 150.0/255.0, 30.0/255.0, 1.0); 
}
```
A VBO is an object that stores colors and vertices; An EBO is an object that stores edges and faces between those vertices; A VAO is an object that manages VBOs and EBOs. All of these are simple arrays, here is an example from learnopengl:
``` cpp
float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};
```
