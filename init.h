#ifndef WEATHER_VISUALIZER_INIT_H
#define WEATHER_VISUALIZER_INIT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
};

struct View {
    glm::mat4 view;
    GLint viewUniform;
    int size;
};

std::string load(const std::string &filename);
std::vector<Vertex> loadOBJ(const std::string& filePath);
GLFWwindow* init_glfw();
void init_glew();
View init_obj_and_shaders();


#endif //WEATHER_VISUALIZER_INIT_H
