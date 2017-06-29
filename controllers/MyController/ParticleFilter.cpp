//
// Created by mohammad on 6/29/2017.
//

#include "ParticleFilter.h"

ParticleFilter::ParticleFilter(const vector<Particle> &particleSet, Map *map, SensorModel *sensorModel) : particleSet(
        particleSet), map(map), sensorModel(sensorModel) {}

