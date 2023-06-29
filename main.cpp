#include "camera.h"
#include "init.h"
#include "particles.h"
#include "weather.h"

int main() {
    std::string cityPositions[9][2]  = {{"50.63", "3.06"}, // Lille
                                       {"48.85", "2.35"}, // Paris
                                       {"45.75", "4.85"}, // Lyon
                                       {"43.61", "3.87"}, // Marseille
                                       {"48.58", "7.75"}, // Strasbourg
                                       { "47.22", "-1.55" },// Nantes
                                        {"46.19", "6.77"}, // Avoriaz
                                        {"74.03", "111.53"}, // Nordvik
                                        {"36.82", "10.17"}}; // Tunis

    WeatherInfo apiResponse = getWeatherData(cityPositions[5][0], cityPositions[5][1]);

    GLFWwindow* window = init_glfw();

    init_glew();

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    GLuint vertexBuffer;
    View v = init_obj_and_shaders(vertices, vertexBuffer);
    setWeatherDisplay(apiResponse);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        v.view = look_at(v.viewUniform);

        if (particleType != NONE){
            updateParticles();
        }

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
