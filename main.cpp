#include <curl/curl.h>

#include "json.hpp"
#include "camera.h"
#include "init.h"
#include "particles.h"

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

std::string getWeatherData() {
    CURL* curl;
    CURLcode res;
    std::string apiResponse;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // Get the meteo info from Paris
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=48.85&longitude=2.35&hourly=temperature_2m,rain&forecast_days=1");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Failed to perform API request: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            json data = json::parse(apiResponse);
            json hourly = data["hourly"];
            json rain = hourly["rain"];
            std::cout << rain << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return apiResponse;
}

int main() {
    std::string apiResponse = getWeatherData();

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
