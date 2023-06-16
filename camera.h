//
// Created by jeanf on 6/16/23.
//

#ifndef WEATHER_VISUALIZER_CAMERA_H
#define WEATHER_VISUALIZER_CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>


extern GLuint bunny_vao_id;
extern GLuint program_id;

void frustum(GLfloat data[16],
             const float &left, const float &right,
             const float &bottom, const float &top,
             const float &z_near, const float &z_far
);

void look_at(GLfloat data[16],
             const float &eyeX, const float &eyeY, const float &eyeZ,
             const float &centerX, const float &centerY, const float &centerZ,
             float upX, float upY, float upZ
);

void update_position(GLuint program_id);

void mouse_motion_callback(int x, int y);

void mouse_wheel_callback(int, int dir, int, int);

void mouse_callback(int button, int, int x, int y);

#endif //WEATHER_VISUALIZER_CAMERA_H
