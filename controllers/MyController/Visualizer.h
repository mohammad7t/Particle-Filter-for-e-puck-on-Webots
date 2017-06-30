//
// Created by mohammad on 6/22/2017.
//

#ifndef MYCONTROLLER_VISUALIZER_H
#define MYCONTROLLER_VISUALIZER_H

#include "ParticleFilter.h"

class IController {
public:
    virtual int nextStep() {
        return -1;
    }
};

class Visualizer {
public:
    IController *controller;
    ParticleFilter *particleFilter;
    bool doDisplay;
    Map *map;
    int cellSize;

    void runController(IController *controller);

    Visualizer(int argc, char **argv);

    void display();

    void idle();

    void visualize(ParticleFilter *particleFilter);

    virtual ~Visualizer();

    void runWithoutController();

    Point convert(const Point &p);

    void vertexPoint(const Point &p);

    void drawCell(int row, int col);
};


#endif //MYCONTROLLER_VISUALIZER_H
