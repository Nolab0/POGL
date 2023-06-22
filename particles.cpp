#include <GL/glew.h>
#include <cstdlib>
#include "particles.h"

particle particles[MAX_PARTICLES];

int loop;

void init_particle(int i) {
    particles[i].life = 1.0;
    particles[i].fade = float(rand()%100)/1000.0f+0.003f;

    particles[i].xpos = (float) (rand() % 21) - 10;
    particles[i].ypos = 15.0;
    particles[i].zpos = (float) (rand() % 21) - 10;

    particles[i].red = 0.5;
    particles[i].green = 0.5;
    particles[i].blue = 1.0;

    particles[i].vel = 0;
    particles[i].gravity = -0.8;
}

void init_particles(){
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        init_particle(loop);
    }
}

void drawRain() {
    float x, y, z;
    for (loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
        x = particles[loop].xpos;
        y = particles[loop].ypos;
        z = particles[loop].zpos;

        glColor3f(1, 1, 1.0);
        glBegin(GL_LINES);
        glVertex3f(x, y, z);
        glVertex3f(x, y+0.5, z);
        glEnd();

        particles[loop].ypos += particles[loop].vel / (2*1000);
        particles[loop].vel += particles[loop].gravity;
        particles[loop].life -= particles[loop].fade;

        if (particles[loop].ypos <= -10) {
            particles[loop].life = -1.0;
        }
        if (particles[loop].life < 0.0) {
            init_particle(loop);
        }
    }
}