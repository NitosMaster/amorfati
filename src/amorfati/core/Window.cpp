#include "Window.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

namespace amorfati {
    Window::Window(int width, int height, const std::string& title) {
        //«== if glfw fails to initialize ==»//
        if (!glfwInit()) {
            std::cerr << "GLFW was caught lackin!\n";
            return;
        }
        
        //«== using c_str() because glfw is a .c lib, idk if .cpp str may cause issues later==»//
        //«==fullscreen with glfwGetPrimaryMonitor() ==»//
        mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, glfwGetPrimaryMonitor());
        
        if (!mWindow) {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(mWindow);

        //«== if glad fails to initialize ==»//
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "GLAD was caught lackin!\n";
            return;
        }
    }
}
