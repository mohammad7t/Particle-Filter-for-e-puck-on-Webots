#pragma once

#include "Point.h"

class Particle {
public:
    Particle(void);

    ~Particle(void);

    Point position;
    double angle;
};

