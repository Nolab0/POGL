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

void init_particle(int i, unsigned long particleSize, unsigned long offset) {
    particles[i].life = 1.0;

    moveObjectToPosition(vertices.begin() + offset + i * particleSize, vertices.begin() + offset + (i+1) * particleSize, glm::vec3((float) (rand() % 21) - 10 + (float)(rand() % 100) / 100.0, 10.0 + (float)(rand() % 10) + ((float)(rand() % 100) / 100.0f), (float) (rand() % 21) - 10  + (float)(rand() % 100) / 100.0));
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

void init_particles(const std::vector<Vertex>& particle, unsigned long offset) {
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        vertices.insert(vertices.end(), particle.begin(), particle.end());
        init_particle(loop, particle.size(), offset);
    }
}

void updateParticles() {
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        for (int i = 0; i < particleSize; i++) {
            vertices[(houseSize + loop * particleSize) + i].position.y += particles[loop].vel / (2 * 1000);
        }
        particles[loop].vel += particles[loop].gravity;

        if (vertices[(houseSize + loop * particleSize)].position.y <= 0) {
            particles[loop].life = -1.0;
        }
        if (particles[loop].life < 0.0) {
            init_particle(loop, particleSize, houseSize);
        }
    }
}