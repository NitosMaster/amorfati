#include<iostream>
#include<amorfati/core/Window.h>
#include<amorfati/core/Shader.h>
#include<amorfati/factories/CreateVAO.h>
#include<amorfati/factories/CreateVertFrag.h>

int main () {
    amorfati::PrintStatus();
    amorfati::Window window(1280, 720, "aim r fatty");

    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    unsigned int edges[] = {
        0, 1, 3,
        1, 2, 3
    };

    amorfati::Shader test = amorfati::CreateVertFrag();
    unsigned int vao = amorfati::CreateVAO(vertices, sizeof(vertices), edges, sizeof(edges));

    while (!window.ShouldClose()) {
        window.Update(0, 0, 0, 1);
        //test.useShader();
        test.setVec4("uColor", 0.6f, 0.2f, 0.4f, 1.0f);
        test.useShader();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    return 0;
}
