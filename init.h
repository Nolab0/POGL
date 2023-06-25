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
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Material {
    std::string name;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
};


struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec3 color; // Added color attribute
};

struct View {
    glm::mat4 view;
    GLint viewUniform;
    unsigned long size;
    unsigned long waterDropSize;
    unsigned long houseSize;
};

std::string load(const std::string &filename);
GLFWwindow* init_glfw();
void init_glew();
View init_obj_and_shaders(std::vector<Vertex> &vertices,  GLuint &vertexBuffer);


#endif //WEATHER_VISUALIZER_INIT_H
