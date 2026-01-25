#include <amorfati/core/Window.h>

int main () {
    amorfati::PrintEngineStatus();
    
    amorfati::Window window(1280, 720, "Amor Fati Engine");
    
    float r;
    float g;
    float b;
    float a;

    std::cout << "\nred? ";
    std::cin >> r;
    std::cout << "green? ";
    std::cin >> g;
    std::cout << "blue? ";
    std::cin >> b;

    while (!window.ShouldClose()) {
        window.Update(r, g, b, a);
    }

    return 0;
}
