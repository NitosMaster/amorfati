#pragma once
#include <iostream>
#include <string>

struct GLFWwindow;

namespace amorfati {
    class Window {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();
        
        bool ShouldClose() const;
        void Update();

    private:
        GLFWwindow* mWindow;
    };

    void PrintEngineStatus();
}
