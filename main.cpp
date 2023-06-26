#include "camera.h"
#include "init.h"
#include "particles.h"

int main() {

    GLFWwindow* window = init_glfw();

    init_glew();

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    GLuint vertexBuffer;
    View v = init_obj_and_shaders(vertices, vertexBuffer);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        v.view = look_at(v.viewUniform);

        updateParticles(vertices, v.waterDropSize, v.houseSize);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glDrawArrays(GL_TRIANGLES, 0, v.size);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
