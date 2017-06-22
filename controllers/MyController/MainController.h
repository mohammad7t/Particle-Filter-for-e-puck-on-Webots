#ifndef CPP_CONTROLLER_H
#define CPP_CONTROLLER_H

#include "common.h"
#include "Odometry.h"

class MainController : public DifferentialWheels {
public:
    Odometry odometry;
    DistanceSensor *sensor[SENSORS];
    double sensorValue[SENSORS];
    const double *accValue;
    Accelerometer *accelerometer;
    int speed[2];
    int stepNumber;
    MainController();
    virtual ~MainController();
    void readSensorValues();
    void loop();
    void run();
};

#endif // CPP_CONTROLLER_H
