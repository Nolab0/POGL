#include "camera.h"
#include "init.h"

float cameraSpeed = 0.05f;
glm::vec3 cameraPosition = glm::vec3(0.0f, 5.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(1.0f, -0.6f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float lastX = 400.0f;
float lastY = 300.0f;
float yaw = -90.0f;
float pitch = 0.0f;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            firstMouse = true;
        } else if (action == GLFW_RELEASE) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

// Mouse movement callback function
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        float xOffset = xpos - lastX;
        float yOffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        // Clamp pitch to avoid flipping the camera
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }
}

void updateFog(){
    GLint fogStartDistanceUniform = glGetUniformLocation(program_id, "fogStart");
    glUniform1f(fogStartDistanceUniform, fogStartDistance);
}

void updateTemp(){
    GLint temperatureUniform = glGetUniformLocation(program_id, "temperature");
    glUniform1f(temperatureUniform, temperature);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // Move camera based on arrow key input
    float cameraSpeedMultiplier = 5.0f;
    if (key == GLFW_KEY_UP) {
        cameraPosition += cameraSpeed * cameraSpeedMultiplier * cameraFront;
    }
    if (key == GLFW_KEY_DOWN) {
        cameraPosition -= cameraSpeed * cameraSpeedMultiplier * cameraFront;
    }
    if (key == GLFW_KEY_LEFT) {
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * cameraSpeedMultiplier;
    }
    if (key == GLFW_KEY_RIGHT) {
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * cameraSpeedMultiplier;
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        set_snow();
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        set_rain();
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        if (fogStartDistance < 500){
            fogStartDistance = 500;
        }
        else
        {
            fogStartDistance = 15;
        }
        updateFog();
    }

    if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
        fogStartDistance += 5;
        updateFog();
    }
    if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
        if (fogStartDistance > 5)
            fogStartDistance -= 5;
        updateFog();
    }
    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        temperature += 5;
        updateTemp();
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        temperature -= 5;
        updateTemp();
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        set_sun();
    }
}

glm::mat4 look_at(GLint viewUniform){
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    return view;
}