#include <amorfati/core/Window.h>
#include <amorfati/core/Shader.h>

int main () {
    const char* vertexPath = "/home/CompSci/amorfati/assets/shaders/test.vert";
    const char* fragPath = "/home/CompSci/amorfati/assets/shaders/test.frag";

    amorfati::PrintStatus()
    amorfati::Window window(1280, 720, "aim r fatty");
    amorfati::Shader test(vertexPath, fragPath);

    while (!window.ShouldClose()) {
        window.Update(0, 0, 0, 1);
        test.useShader();
        
    }

    return 0;
}
