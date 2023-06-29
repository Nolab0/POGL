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

#ifndef WEATHER_VISUALIZER_INIT_H
#define WEATHER_VISUALIZER_INIT_H

struct Material {
    std::string name;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
};

struct View {
    glm::mat4 view;
    GLint viewUniform;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 originalPosition;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec3 color;
};

enum ParticleType {
    NONE,
    RAIN,
    SNOW,
    HAIL
};


extern std::vector<Vertex> vertices;
extern float fogStartDistance;
extern GLuint program_id;
extern ParticleType particleType;
extern unsigned long sceneSize;
extern unsigned long particleSize;
extern float temperature;

void updateTemp();
void updateFog();
std::string load(const std::string &filename);
GLFWwindow* init_glfw();
void init_glew();
View init_obj_and_shaders(std::vector<Vertex> &vertices,  GLuint &vertexBuffer);
void set_snow();
void set_rain();
void set_sun();
void set_hail();
void impactSnow(float x, float z);
void displaySplash(float x, float z, int iter, int &splashIndex);
void deleteCircle3(int splashIndex);

#endif //WEATHER_VISUALIZER_INIT_H
