#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <math.h>
#include <vector>

using namespace std;

const int TIME_STEP = 64;
const double WHEEL_RADIUS = 0.0205;
const double AXLE_LENGTH = 0.052;
const double ENCODER_RESOLUTION = 159.23;
const int RANGE = (1024 / 2);
const int SENSORS = 8; //
const int DISTANCES = 7;
const double RADIUS_ROBOT = 3.7;

#define SHOW(x) #x << '=' << (x) << ' '
#define LOG(x) cout << SHOW(x) << endl;
#define X(point) ((point).real())
#define Y(point) ((point).imag())

double randZeroToOne();

double randMToN(double M, double N);

template<typename T>
std::ostream &operator<<(std::ostream &out, const vector<T, std::allocator<T>> &rhs) {
    out << '{';
    for (int i = 0; i < rhs.size(); i++) {
        out << rhs[i];
        if (i + 1 < rhs.size()) {
            out << ',';
        }
    }
    out << '}';
    return out;
}

#endif // COMMON_H_INCLUDED
