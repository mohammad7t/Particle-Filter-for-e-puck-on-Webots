#include "Odometry.h"

Odometry::Odometry() {}

Odometry::Odometry(DifferentialWheels *robot) {
    this->robot = robot;
}

void Odometry::update() {
    double l = robot->getLeftEncoder();
    double r = robot->getRightEncoder();
    double dl = l / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by left wheel in meter
    double dr = r / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by right wheel in meter
    a = (dr - dl) / AXLE_LENGTH;
    d = (dr + dl) / 2;
}

Action Odometry::getAction() {
    Action action;
    action.distance = max(0.0, 100 * (d - lastD) - 2);
    action.rotateRadian = a - lastA;
    lastD = d;
    lastA = a;

    return action;
}

