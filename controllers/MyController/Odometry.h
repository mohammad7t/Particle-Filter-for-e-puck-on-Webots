#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "common.h"
#include "Action.h"
#include <webots/DifferentialWheels.hpp>
using namespace webots;

class Odometry {
public:
    double a, d;
    double lastA, lastD;

    Action getAction();
    DifferentialWheels *robot;

    void update();

    Odometry(DifferentialWheels *robot, double motionModelSpeed);

    Odometry();

    double motionModelSpeed;
};

#endif // ODOMETRY_H
