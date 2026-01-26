#include <amorfati/core/Window.h>
#include <amorfati/core/Shader.h>

int main () {
    amorfati::PrintEngineStatus();
    
    amorfati::Window window(1280, 720, "aim r fatty");

    while (!window.ShouldClose()) {
        window.Update(0, 0, 0, 1);
    }
    
    const char* vertexPath = "~/CompSci/amorfati/assets/shaders/test.vert";
    const char* fragPath = "~/CompSci/amorfati/assets/shaders/test.frag";

    amorfati::Shader(vertexPath, fragPath);
    useShader();

    return 0;
}
