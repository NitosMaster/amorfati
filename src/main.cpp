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
    amorfati::Window window(800, 800, "amor fati - perspective demo");
    amorfati::Shader shader = amorfati::CreateVertFrag();

    float vertices[] = {
         0.0f,  0.3f, 0.0f,
        -0.3f, -0.3f, 0.0f,
         0.3f, -0.3f, 0.0f,
    };
    unsigned int edges[] = { 0, 1, 2 };
    unsigned int VAO = amorfati::CreateVAO(vertices, sizeof(vertices), edges, sizeof(edges));

    Matrix projection = Matrix::Project(45.0f * 3.14159f / 180.0f, 1.0f, 0.1f, 100.0f);

    Vector eye(3), target(3), up(3);
    eye[0] = 0.0f; eye[1] = 0.0f; eye[2] = 5.0f;
    target[0] = 0.0f; target[1] = 0.0f; target[2] = 0.0f;
    up[0] = 0.0f; up[1] = 1.0f; up[2] = 0.0f;
    Matrix view = Matrix::View(eye, target, up);

    Vector axisZ(3), axisY(3), axisX(3);
    axisZ[0] = 0.0f; axisZ[1] = 0.0f; axisZ[2] = 1.0f;
    axisY[0] = 0.0f; axisY[1] = 1.0f; axisY[2] = 0.0f;
    axisX[0] = 1.0f; axisX[1] = 0.0f; axisX[2] = 0.0f;

    float time = 0.0f;

    while (!window.ShouldClose()) {
        time += 0.02f;

        shader.useShader();
        window.Update(0.05f, 0.05f, 0.1f, 1.0f);

        for (int i = 0; i < 3; i++) {
            float depth = -4.0f + 3.0f * sin(time * 0.5f + i * 2.0f);
            float spinSpeed = 1.0f + i * 0.3f;
    
            Vector pos(3);
            pos[0] = (i - 1) * 1.2f;
            pos[1] = 0.0f;
            pos[2] = depth;
            Matrix translate = Matrix::Translate(pos);

            Matrix rotZ = Matrix::Rotate(axisZ, time * spinSpeed);
            Matrix rotY = Matrix::Rotate(axisY, time * spinSpeed * 0.7f);
            Matrix model = translate * rotZ * rotY;

            Matrix mvp = projection * view * model;

            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, mvp.getRawData());

            float hue = (i / 3.0f) * 6.28f + time;
            float r = (sin(hue) + 1.0f) / 2.0f;
            float g = (sin(hue + 2.094f) + 1.0f) / 2.0f;
            float b = (sin(hue + 4.188f) + 1.0f) / 2.0f;
            shader.setVec4("uColor", r, g, b, 1.0f);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        }

        window.SwapBuffer();
    }

    return 0;
}
