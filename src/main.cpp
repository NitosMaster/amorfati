#include <amorfati/core/Window.h>

int main () {
    amorfati::PrintEngineStatus();
    
    amorfati::Window window(1280, 720, "Amor Fati Engine");

    while (!window.ShouldClose()) {
        window.Update();
    }

    return 0;
}
