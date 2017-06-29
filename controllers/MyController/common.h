#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <math.h>

using namespace std;

const int TIME_STEP = 64;
const double WHEEL_RADIUS = 0.0205;
const double AXLE_LENGTH = 0.052;
const double ENCODER_RESOLUTION = 159.23;
const int RANGE = (1024 / 2);
const int SENSORS = 8; //
const int DISTANCES = 7;
const double ROBOT_RADIUS = 3.7;

#define X(point) ((point).real())
#define Y(point) ((point).imag())

double randZeroToOne();

double randMToN(double M, double N);

#endif // COMMON_H_INCLUDED
