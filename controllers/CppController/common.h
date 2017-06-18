#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <webots/DifferentialWheels.hpp>
#include <iostream>

using namespace std;
using namespace webots;

const int TIME_STEP = 64;
const double WHEEL_RADIUS = 0.0205;
const double AXLE_LENGTH = 0.052;
const double ENCODER_RESOLUTION = 159.23;
const int RANGE = (1024 / 2);
const int SENSORS = 8; //

#endif // COMMON_H_INCLUDED
