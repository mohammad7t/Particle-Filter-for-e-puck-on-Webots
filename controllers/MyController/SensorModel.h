#pragma once

#include "common.h"
#include "Particle.h"
#include "Observation.h"
#include "Map.h"

// SENSOR ORIENTATION RADIAN
#define S0_ORIENTATION 1.27
#define S1_ORIENTATION 0.77
#define S2_ORIENTATION 0.0
#define S3_ORIENTATION 5.21
#define S4_ORIENTATION 4.21
#define S5_ORIENTATION 3.14159
#define S6_ORIENTATION 2.37
#define S7_ORIENTATION 1.87

#include <math.h>
#include "Observation.h"
#include ""

class SensorModel {
public:
    vector<vector<double>> meanSensorVector;
    vector<vector<double>> stdDeviationSensorVector;

    SensorModel(void);

    ~SensorModel(void);

    double calculateProbabilityObservation(Particle particle, Observation observ, Map map);

    double calculateSensorProbabilityObservation(Point point, double observ, Map map);

    void readSensorModelFile();

    double convertSingleSensorValue(double sensorValue); //returns cenitemeter value
    Observation sensorValuesToObservation(double *sensorValues);

};

