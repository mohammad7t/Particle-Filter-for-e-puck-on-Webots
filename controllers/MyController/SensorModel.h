#pragma once

#include "common.h"
#include "Particle.h"
#include "Observation.h"
#include "Map.h"
#include <cmath>
#include "Observation.h"
#include "Gaussian.h"

// SENSOR ORIENTATION RADIAN
#define S0_ORIENTATION 1.27
#define S1_ORIENTATION 0.77
#define S2_ORIENTATION 0.0
#define S3_ORIENTATION 5.21
#define S4_ORIENTATION 4.21
#define S5_ORIENTATION 3.14159
#define S6_ORIENTATION 2.37
#define S7_ORIENTATION 1.87


class SensorModel {
public:
    vector<vector<double>> meanSensorVector;
    vector<vector<double>> stdDeviationSensorVector;
    vector<vector<Gaussian>> distanceSensors;

    SensorModel(const char *meanFilePath, const char *varFilePath);

    ~SensorModel(void);

    void readSensorModelFile(const char *s, const char *meanFilePath);
    void computeDistanceSensors();

    double convertSingleSensorValue(int sensorId, double sensorValue); //returns cenitemeter value
    Gaussian getSensorGaussian(int sensorId, double distance);
    Observation sensorValuesToObservation(double *sensorValues);

    double getObservationProbability(Particle *particle, Observation *observation,Map *world);
};

