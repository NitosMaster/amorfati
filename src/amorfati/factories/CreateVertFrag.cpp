#include<iostream>
#include "CreateVertFrag.h"
#include "../core/Shader.h"

namespace amorfati {
    Shader CreateVertFrag() {
        std::string vCode = R"(
            #version 330 core
            uniform mat4 model;
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = model * vec4(aPos, 1.0);
            }
        )";

        std::string fCode = R"(
            #version 330 core
            out vec4 FragColor;
            uniform vec4 uColor;
            void main() {
                FragColor = uColor;
            }
        )";

        return Shader(vCode, fCode); 
    }
}
