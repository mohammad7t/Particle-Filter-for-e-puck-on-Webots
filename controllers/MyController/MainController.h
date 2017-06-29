#ifndef CPP_CONTROLLER_H
#define CPP_CONTROLLER_H

#include "common.h"
#include "Odometry.h"
#include "ParticleFilter.h"

class MainController : public DifferentialWheels {
public:
    ParticleFilter *particleFilter;
    Odometry odometry;

    DistanceSensor *sensor[SENSORS];

    Observation getObservation();
    double sensorValue[SENSORS];
    const double *accValue;
    Accelerometer *accelerometer;
    int speed[2];
    int stepNumber;

    MainController(ParticleFilter *particleFilter);

    virtual ~MainController();

    void readSensorValues();

    void run();

    int nextStep();
//    const double braitenberg_coefficients[8][2] =
//            { {150, -35}, {100, -15}, {80, -10}, {-10, -10},
//              {-10, -10}, {-10, 80}, {-30, 100}, {-20, 150} };

};

#endif // CPP_CONTROLLER_H
