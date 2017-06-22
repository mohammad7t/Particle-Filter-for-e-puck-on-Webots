#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "common.h"

class Odometry {
public:
    double a, d;
    DifferentialWheels *robot;
    void update();
    Odometry(DifferentialWheels* robot);
    Odometry();
};

#endif // ODOMETRY_H
