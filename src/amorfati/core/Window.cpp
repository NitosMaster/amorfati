#include "Window.h"
#include <glad/gl.h> 
#include <GLFW/glfw3.h>
#include <iostream>

namespace amorfati {
    void PrintEngineStatus() {
        std::cout << "love your lowest lows and your highest highs... amorfati";
    }

    Window::Window(int width, int height, const std::string& title) {
        //«== if glfw fails to initialize ==»//
        if (!glfwInit()) {
            std::cerr << "GLFW was caught lackin!\n";
            return;
        }
        
        mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        
        if (!mWindow) {
            std::cerr << "window is cooked!";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(mWindow);
        
        //«== if glad fails ==»//
        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
            std::cerr << "GLAD was caught lackin!\n";
            return;
        }
    }

    Window::~Window() {
        if (mWindow) {
            glfwDestroyWindow(mWindow);
        }
        glfwTerminate();
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(mWindow);
    }

    void Window::Update() {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }
}
