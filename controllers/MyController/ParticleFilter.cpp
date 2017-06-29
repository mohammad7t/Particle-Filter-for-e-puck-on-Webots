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
    particleSet.reserve(particleSize);
    for (uint i = 0; i < particleSize; i++) {
        particleSet.push_back(map->generateRandomParticle());
    }
}

void ParticleFilter::updateWeights(Observation &observation) {
    for (int i = 0; i < particleSet.size(); i++) {
        Particle &particle = particleSet[i];
        particle.weight = sensorModel->getObservationProbability(&particle, &observation, map);
    }
}

void ParticleFilter::updateParticleSetWithAction(Action *action) {
    for (int i = 0; i < particleSet.size(); ++i) {
        particleSet[i].doAction(action, map);
    }
}

void ParticleFilter::reSampling() {
    double sumWeight = 0;
    vector<double> weightsDivider;
    weightsDivider.push_back(0.0);
    for (int i = 0; i < particleSet.size(); ++i) {
        sumWeight += particleSet[i].weight;
        weightsDivider.push_back(sumWeight);
    }
    cout
            << "sumWeight ====================================================================================================="
            << sumWeight << endl;
    double accumulative = sumWeight;
    for (int i = 0; i < particleSet.size(); ++i) {
        accumulative += particleSet[i].weight;
        weightsDivider.push_back(accumulative);
    }

    double randomNumber = randMToN(0, sumWeight);


    double step = sumWeight / particleSet.size();

    int selectedIndex = 0;
    vector<Particle> newParticleSet;

    for (int j = 0; j < particleSet.size(); ++j) {
        for (int i = selectedIndex; i < weightsDivider.size(); ++i) {
            if (compare(randomNumber, weightsDivider[i + 1]) == -1) {
                selectedIndex = i;
                newParticleSet.push_back(particleSet[selectedIndex % particleSet.size()]);
                break;
            }
        }
        randomNumber = randomNumber + step;
    }
    particleSet = newParticleSet;


}

int ParticleFilter::compare(double d1, double d2) {
    if (abs(d1 - d2) < 1e-9) {
        return 0;
    } else if (d1 - d2 < 0) {
        return -1;
    } else {
        return +1;
    }
}

