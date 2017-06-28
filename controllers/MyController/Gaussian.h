//
// Created by mohammad on 6/28/2017.
//

#ifndef MYCONTROLLER_GUASSIAN_H
#define MYCONTROLLER_GUASSIAN_H

class Gaussian {
public:
    double mean;
    double sigma2;

    Gaussian(double mean, double sigma2);

    Gaussian();

    double getProbability(double d);
};


#endif //MYCONTROLLER_GUASSIAN_H
