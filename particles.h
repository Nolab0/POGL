#ifndef WEATHER_VISUALIZER_PARTICLES_H
#define WEATHER_VISUALIZER_PARTICLES_H


#include "init.h"

#define MAX_PARTICLES 10000
#define MAX_SPLASH 1000

class particle {
public:
    float vel;
    float gravity;
    bool bounce;
    int splashIter;
    int splashIndex;
};

void init_particles(const std::vector<Vertex>& particle, unsigned long offset);
void updateParticles();

#endif //WEATHER_VISUALIZER_PARTICLES_H
