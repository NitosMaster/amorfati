#include <iostream>
#include <cmath>
#include "amorfati/core/Window.h"
#include "amorfati/core/Shader.h"
#include "amorfati/factories/CreateVAO.h"
#include "amorfati/factories/CreateVertFrag.h"
#include "amorfati/math/Matrix.h"
#include "amorfati/math/Vector.h"
#include "amorfati/math/Quaternion.h"

int main() {
    amorfati::PrintStatus();
    amorfati::Window window(800, 800, "amorfati");
    amorfati::Shader shader = amorfati::CreateVertFrag();

    float vertices[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
    };
    unsigned int edges[] = { 0, 1, 2 };

    unsigned int VAO = amorfati::CreateVAO(vertices, sizeof(vertices), edges, sizeof(edges));

    float angle = 0.0f;

    while (!window.ShouldClose()) {
        angle += 0.01f;

        Vector axis(3);
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[2] = 1.0f;

        Matrix rot = Matrix::Rotate(axis, angle);

        float r = (sin(angle) + 1.0f) / 2.0f;
        float g = (sin(angle + 2.094f) + 1.0f) / 2.0f;
        float b = (sin(angle + 4.188f) + 1.0f) / 2.0f;

        shader.useShader();

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, rot.getRawData());

        shader.setVec4("uColor", r, g, b, 1.0f);

        window.Update(0.1f, 0.1f, 0.1f, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        window.SwapBuffer();
    }

    return 0;
}
