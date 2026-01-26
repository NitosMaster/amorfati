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
        //«== alpha is from 0 to 1, while others aren't normalized ==»//
        void Update(float red, float green, float blue, float alpha);

    private:
        GLFWwindow* mWindow;
    };

    void PrintStatus();
}
