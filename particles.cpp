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
    moveObjectToPosition(vertices.begin() + offset + i * particleSize, vertices.begin() + offset + (i+1) * particleSize, glm::vec3((float) (rand() % 21) - 10 + (float)(rand() % 100) / 100.0, 1 + (float)(rand() % 20) + ((float)(rand() % 100) / 100.0f), (float) (rand() % 21) - 10  + (float)(rand() % 100) / 100.0));
    switch (particleType) {
        case RAIN:
            particles[i].vel = -50;
            particles[i].gravity = -0.8;
            particles[i].splashIter = 0;
            break;
        case SNOW:
            particles[i].vel = -10;
            particles[i].gravity = 0;
            break;
        case HAIL:
            particles[i].vel = -50;
            particles[i].gravity = -0.4;
            particles[i].bounce = true;
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
        if (particleType == RAIN && particles[loop].splashIter > 0) {
            if (particles[loop].splashIter == 1 || particles[loop].splashIter == 5 || particles[loop].splashIter == 10)
                displaySplash(vertices[(sceneSize + loop * particleSize)].position.x, vertices[(sceneSize + loop * particleSize)].position.z, particles[loop].splashIter, particles[loop].circleBegin);
            particles[loop].splashIter++;
            if (particles[loop].splashIter > 15){
                particles[loop].splashIter = 0;
                deleteCircle(particles[loop].circleBegin);
            }
            continue;
        }
        for (int i = 0; i < particleSize; i++) {
            vertices[(sceneSize + loop * particleSize) + i].position.y += particles[loop].vel / (2 * 1000);
        }
        particles[loop].vel += particles[loop].gravity;
        if (particleType == HAIL && particles[loop].vel < -70)
            particles[loop].vel = -70;

        if (vertices[(sceneSize + loop * particleSize)].position.y <= 0) {
            if (particleType == HAIL && particles[loop].bounce) {
                particles[loop].vel = -particles[loop].vel - 10;
                particles[loop].gravity = -2;
                particles[loop].bounce = false;
            } else {
                init_particle(loop, particleSize, sceneSize);
                if (particleType == SNOW)
                    impactSnow(vertices[(sceneSize + loop * particleSize)].position.x, vertices[(sceneSize + loop * particleSize)].position.z);
                if (particleType == RAIN){
                    particles[loop].splashIter = 1;
                }
            }
        }
    }
}