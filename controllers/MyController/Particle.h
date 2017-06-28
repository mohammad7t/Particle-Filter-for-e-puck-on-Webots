#pragma once

#include "Point.h"
#include "Action.h"

class Map;

class Particle {
public:
    Particle(void);

    ~Particle(void);

    Point position;

    double angle;

    double weight;

    void doAction(Action action,Map *world);
};

