//
// Created by mohammad on 6/28/2017.
//

#include "Gaussian.h"
#include "cmath"

#include "common.h"
#include <iostream>
#include <random>

double Gaussian::getProbability(double x) {
//    cout << "getProbability: x= " << x << endl;
//    cout << "getProbability: mean= " << mean << endl;
//    cout << "getProbability: var= " << sigma2 << endl;
//    cout << "getProbability: result= " << exp(-pow(x - mean, 2.0) / 2 / sigma2) / sqrt(2 * M_PI * sigma2) << endl;

    double result = exp(-pow(x - mean, 2.0) / 2 / sigma2) / sqrt(2 * M_PI * sigma2) + 1;
    return result;
    return 1 / (abs(mean - x) + 1);
}

Gaussian::Gaussian(double mean, double sigma2) : mean(mean), sigma2(sigma2) {}

Gaussian::Gaussian() : mean(0.0), sigma2(0.0) {}

std::default_random_engine generator;

double Gaussian::getSample(double mean, double variance) {
    std::normal_distribution<double> distribution(mean, variance);
    double temp = distribution(generator);
    //LOG(temp);
    return temp;
}

std::ostream &operator<<(std::ostream &out, const Gaussian &rhs) {
    out << "N(" << rhs.mean << "," << rhs.sigma2 << ')';
    return out;
}
