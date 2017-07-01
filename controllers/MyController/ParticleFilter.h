//
// Created by mohammad on 6/29/2017.
//

#ifndef MYCONTROLLER_PARTICLEFILTER_H
#define MYCONTROLLER_PARTICLEFILTER_H

#include <vector>
#include <random>
#include "Particle.h"
#include "Map.h"
#include "SensorModel.h"
#include "Action.h"

class ParticleFilter {
public:
    int version;
    vector<Particle> particleSet;
    Map *map;
    SensorModel *sensorModel;

    ParticleFilter(const vector<Particle> &particleSet, Map *map, SensorModel *sensorModel1);
    ParticleFilter(unsigned int particleSize, Map *map1, SensorModel *sensorModel1);

    void updateWeights(Observation &observation);

    void updateParticleSetWithAction(Action *action, double dVar, double aVar);

    void reSampling();

    void tickVersion();

    // if d1 - d2 < 10e-9 : return 0;
    // else if d1 - d2 < 0  : return -1;
    // else if d1 - d2 > 0  : return +1;
    int compare(double d1, double d2);
};


#endif //MYCONTROLLER_PARTICLEFILTER_H
