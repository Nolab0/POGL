#include "camera.h"
#include "init.h"
#include "particles.h"

int main() {

    GLFWwindow* window = init_glfw();

    init_glew();

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    View v = init_obj_and_shaders();

    init_particles();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        v.view = look_at(v.viewUniform);

        drawRain();

        glDrawArrays(GL_TRIANGLES, 0, v.size);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
