//
// Created by mohammad on 6/29/2017.
//

#include "ParticleFilter.h"

typedef unsigned int uint;

ParticleFilter::ParticleFilter(const vector<Particle> &particleSet, Map *map, SensorModel *sensorModel) : particleSet(
        particleSet), map(map), sensorModel(sensorModel) {
    this->map = map;
}

ParticleFilter::ParticleFilter(uint particleSize, Map *map, SensorModel *sensorModel) : map(map),
                                                                                        sensorModel(sensorModel) {
    vector<Particle> particles(particleSize);
    for (uint i = 0; i < particleSize; i++) {
        particles[i] = map->generateRandomParticle();
    }
}

