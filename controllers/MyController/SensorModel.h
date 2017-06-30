#pragma once

#include "common.h"
#include "Particle.h"
#include "Observation.h"
#include "Map.h"
#include <cmath>
#include "Observation.h"
#include "Gaussian.h"

const double SENSOR_ORIENTATION[] = {1.27, .77, 0.0, 5.21, 4.21, 3.14159, 2.37, 1.87};


class SensorModel {
public:
    vector<vector<double>> meanSensorVector;
    vector<vector<double>> stdDeviationSensorVector;

    SensorModel(const char *meanFilePath, const char *varFilePath);

    ~SensorModel(void);

    void readSensorModelFile(const char *s, const char *meanFilePath);

    double convertSingleSensorValue(int sensorId, double sensorValue); //returns cenitemeter value
    Gaussian getSensorGaussian(int sensorId, double distance);
    Observation sensorValuesToObservation(double *sensorValues);

    double getObservationProbability(Particle *particle, Observation *observation,Map *world);

    Observation getExpectedObservation(const Particle *particle, Map *world) const;
};

