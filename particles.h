#ifndef WEATHER_VISUALIZER_PARTICLES_H
#define WEATHER_VISUALIZER_PARTICLES_H


#include "init.h"

#define MAX_PARTICLES 1000

class particle {
public:
    float life;
    float fade;
    float vel;
    float gravity;
    unsigned long index;
};

void init_particles(const std::vector<Vertex>& waterDrop, unsigned long offset, std::vector<Vertex> &vertices);
void updateRain(std::vector<Vertex> &vertices, int waterDropSize, int offset);

#endif //WEATHER_VISUALIZER_PARTICLES_H
