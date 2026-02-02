# this is just to keep track of concepts

## goal
I'm not sure exactly how high level I want this game engine to be but I'd like to make me never have to touch .vert, .frag and openGL funcs. Additionally I believe the scripting lang is going to be customizable and that means I'll have to do some .so/.ddl magic I'm going to delay as much as I can. As I want the engine to be fully customizable I plan on adding a config file the user can edit, to change certain core characteristics of the engine to their hearts desire. This config will be declaritive like NixOS. I also plan on adding a plugin system that allows a plugin to change the inner workings of func presets like addVector(), this means you would have a LOT of functions the engine uses but you can always tell the engine through your config to use the function of a plugin instead. Each plugin could have a map system. It "maps" each pluginFunc to a engineFunc. This allows a user to change the way a default gravity function works without having multiple funcs for it, and instead one with the specific functionality the user wants, like not weight based gravity but speed based gravity, without having to make gravity from scratch. Further I hope to make a lot of capabilities flexible. This means they support multiple dimensions, types of geometry, types of numbers like infinity, etc. In other words attempt to make a user declare: "dimensions = 4" and adjust the physics and math for that auto. Ik it's hard. Another point of interest for me is creating different versions of the engine depending on what the user wants, such as: optimized but may not work on your machine engine version, high-level engine version, low-level engine version, highly portable but sub-optimized engine version, etc. I don't like when a piece of software comes with 3 million things pre installed that I don't give a rats ass about.
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
