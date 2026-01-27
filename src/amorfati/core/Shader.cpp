#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace amorfati {
    Shader::Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vertShader; // v for "vert"
        std::ifstream fragShader; // f for "frag"

        vertShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        
        try {
            vertShader.open(vertexPath);
            fragShader.open(fragmentPath);
            std::stringstream vStream, fStream;
            vStream << vertShader.rdbuf();
            fStream << fragShader.rdbuf();
            vertShader.close();
            fragShader.close();
            vertexCode = vStream.str();
            fragmentCode = fStream.str();
        } catch (std::ifstream::failure& e) {
            std::cout << "Shader file was caught lackin!\n";
        }

        const char* vSource = vertexCode.c_str();
        const char* fSource = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char debug[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vSource, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, debug);
            std::cout << "vertex caught lackin:\n" << debug << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fSource, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, debug);
            std::cout << "fragment caught lackin:\n" << debug << std::endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, debug);
            std::cout << "program (insert zelda protagonist here) caught lackin:\n" << debug << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::useShader() {
        glUseProgram(ID);
    }

    void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
}

