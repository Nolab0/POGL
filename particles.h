#ifndef WEATHER_VISUALIZER_PARTICLES_H
#define WEATHER_VISUALIZER_PARTICLES_H


#include "init.h"

#define MAX_PARTICLES 10000

enum ParticleType {
    RAIN,
    SNOW
};

class particle {
public:
    float life;
    float vel;
    float gravity;
};

void init_particles(const std::vector<Vertex>& waterDrop, unsigned long offset, std::vector<Vertex> &vertices);
void updateParticles(std::vector<Vertex> &vertices, int waterDropSize, int offset);

#endif //WEATHER_VISUALIZER_PARTICLES_H
