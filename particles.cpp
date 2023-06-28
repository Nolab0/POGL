#include <cstdlib>
#include "particles.h"
#include "init.h"

particle particles[MAX_PARTICLES];

int loop;

void moveObjectToPosition(std::vector<Vertex>::iterator begin, std::vector<Vertex>::iterator end, const glm::vec3& absolutePosition) {
    for (auto it = begin; it != end; ++it) {
        it->position += absolutePosition;
    }
}

void init_particle(int i, unsigned long waterDropSize, unsigned long offset) {
    particles[i].life = 1.0;

    moveObjectToPosition(vertices.begin() + offset + i * waterDropSize, vertices.begin() + offset + (i+1) * waterDropSize, glm::vec3((float) (rand() % 21) - 10 + (float)(rand() % 100) / 100.0, 10.0 + (float)(rand() % 10) + ((float)(rand() % 100) / 100.0f), (float) (rand() % 21) - 10  + (float)(rand() % 100) / 100.0));
    switch (particleType) {
        case RAIN:
            particles[i].vel = -50;
            particles[i].gravity = -0.8;
            break;
        case SNOW:
            particles[i].vel = -10;
            particles[i].gravity = 0;
            break;
    }
}

void init_particles(const std::vector<Vertex>& waterDrop, unsigned long offset) {
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        vertices.insert(vertices.end(), waterDrop.begin(), waterDrop.end());
        init_particle(loop, waterDrop.size(), offset);
    }
}

void updateParticles(int waterDropSize, int offset) {
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        for (int i = 0; i < waterDropSize; i++) {
            vertices[(offset + loop * waterDropSize) + i].position.y += particles[loop].vel / (2 * 1000);
        }
        particles[loop].vel += particles[loop].gravity;

        if (vertices[(offset + loop * waterDropSize)].position.y <= -5) {
            particles[loop].life = -1.0;
        }
        if (particles[loop].life < 0.0) {
            init_particle(loop, waterDropSize, offset);
        }
    }
}