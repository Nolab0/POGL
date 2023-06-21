#ifndef WEATHER_VISUALIZER_CAMERA_H
#define WEATHER_VISUALIZER_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
glm::mat4 look_at(GLint viewUniform);

#endif //WEATHER_VISUALIZER_CAMERA_H
