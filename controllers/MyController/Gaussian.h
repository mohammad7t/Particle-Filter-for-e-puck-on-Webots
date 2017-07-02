//
// Created by mohammad on 6/28/2017.
//

#ifndef MYCONTROLLER_GUASSIAN_H
#define MYCONTROLLER_GUASSIAN_H

#include "common.h"

class Gaussian {
public:
    double mean;
    double sigma2;

    Gaussian(double mean, double sigma2);

    Gaussian();

    double getProbability(double d);

    double getSample(double mean, double variance);
};

std::ostream &operator<<(std::ostream &out, const Gaussian &rhs);

#endif //MYCONTROLLER_GUASSIAN_H
