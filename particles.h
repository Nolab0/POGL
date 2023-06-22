#ifndef WEATHER_VISUALIZER_PARTICLES_H
#define WEATHER_VISUALIZER_PARTICLES_H


#define MAX_PARTICLES 1000

class particle {
public:
    float life;
    float fade;
    float red;
    float green;
    float blue;
    float xpos;
    float ypos;
    float zpos;
    float vel;
    float gravity;
};

void init_particles();
void drawRain();

#endif //WEATHER_VISUALIZER_PARTICLES_H
