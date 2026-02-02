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
        void Update(float red, float green, float blue, float alpha);
        void SwapBuffer();

    private:
        GLFWwindow* mWindow;
    };

    void PrintStatus();
}
