//
// Created by mohammad on 6/29/2017.
//

#ifndef MYCONTROLLER_PARTICLEFILTER_H
#define MYCONTROLLER_PARTICLEFILTER_H

#include <vector>
#include "Particle.h"
#include "Map.h"
#include "SensorModel.h"

class ParticleFilter {
public:
    vector<Particle> particleSet;
    Map *map;
    SensorModel *sensorModel;

    ParticleFilter(const vector<Particle> &particleSet, Map *map, SensorModel *sensorModel1);

    ParticleFilter(unsigned int particleSize, Map *map1, SensorModel *sensorModel1);

    void updateWeights(Observation &observation) {
        for (int i = 0; i < particleSet.size(); i++) {
            Particle &particle = particleSet[i];
            particle.weight = sensorModel->getObservationProbability(&particle, &observation, map);
        }
    }
};


#endif //MYCONTROLLER_PARTICLEFILTER_H
