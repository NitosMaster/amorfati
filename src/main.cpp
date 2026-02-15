#include <iostream>
#include <cmath>
#include <vector>
#include <amorfati/core/Window.h>
#include <amorfati/core/Shader.h>
#include <GLFW/glfw3.h>
#include <amorfati/factories/CreateVAO.h>
#include <amorfati/factories/CreateVertFrag.h>
#include <amorfati/math/Matrix.h>
#include <amorfati/math/Vector.h>

int main() {
    amorfati::PrintStatus();
    amorfati::Window window(1280, 720, "amorfati engine");

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int edges[] = {
        0, 1, 3,
        1, 2, 3
    };

    amorfati::Shader test = amorfati::CreateVertFrag();
    unsigned int vao = amorfati::CreateVAO(vertices, sizeof(vertices), edges, sizeof(edges));

    Vector v1(3); 
    v1[0] = 1.0f; v1[1] = 0.0f; v1[2] = 0.0f;
    Vector v2(3);
    v2[0] = 0.0f; v2[1] = 1.0f; v2[2] = 0.0f;
    
    Vector v3 = v1.cross(v2);

    while (!window.ShouldClose()) {
        window.Update(0.05f, 0.05f, 0.1f, 1.0f);

        float time = (float)glfwGetTime();
        float scale = std::sin(time) * 0.2f + 0.8f;
        float angle = time * 1.5f;

        Matrix transform = Matrix::Identity(4);

        float c = std::cos(angle) * scale;
        float s = std::sin(angle) * scale;

        transform(0, 0) = c;  transform(0, 1) = -s;
        transform(1, 0) = s;  transform(1, 1) = c;

        test.useShader();
        
        float r = std::sin(time * 0.5f) * 0.5f + 0.5f;
        test.setVec4("uColor", r, 0.2f, 0.4f, 1.0f);

        int loc = glGetUniformLocation(test.ID, "uTransform");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transform.getRawData());

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.SwapBuffer();
    }

    return 0;
}
