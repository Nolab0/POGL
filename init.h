//
// Created by jeanf on 6/16/23.
//

#ifndef WEATHER_VISUALIZER_INIT_H
#define WEATHER_VISUALIZER_INIT_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "camera.h"
#include "bunny.hh"

void init_glut(int &argc, char *argv[]);
bool init_glew();
void init_GL();
bool init_shaders();
void init_object();

#endif //WEATHER_VISUALIZER_INIT_H
