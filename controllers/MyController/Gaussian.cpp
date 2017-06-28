//
// Created by mohammad on 6/28/2017.
//

#include "Gaussian.h"
#include "cmath"

#include "common.h"
#include <iostream>

double Gaussian::getProbability(double x) {
    cout<<"getProbability: x= "<<x<<endl;
    cout<<"getProbability: mean= "<<mean<<endl;
    cout<<"getProbability: var= "<<sigma2<<endl;
    cout<<"getProbability: result= "<<exp(-pow(x - mean, 2.0) / 2 / sigma2) / sqrt(2 * M_PI * sigma2)<<endl;
    return exp(-pow(x - mean, 2.0) / 2 / sigma2) / sqrt(2 * M_PI * sigma2);
}

Gaussian::Gaussian(double mean, double sigma2) : mean(mean), sigma2(sigma2) {}

Gaussian::Gaussian() : mean(0.0), sigma2(0.0) {}
