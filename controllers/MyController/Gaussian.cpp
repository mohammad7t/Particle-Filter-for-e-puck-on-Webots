//
// Created by mohammad on 6/28/2017.
//

#include "Gaussian.h"
#include "cmath"

double Gaussian::getProbability(double x) {
    return 1 / sqrt(2 * M_PI * sigma2) * exp(-pow(x - mean, 2.0) / 2 / sigma2);
}
