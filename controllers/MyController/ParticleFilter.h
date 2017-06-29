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

    void updateWeights(Observation &observation) {
        for (auto &particle : particleSet) {
            particle.weight = sensorModel->getObservationProbability(&particle, &observation, map);
        }
    }
};


#endif //MYCONTROLLER_PARTICLEFILTER_H
