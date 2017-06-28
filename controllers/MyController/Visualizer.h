//
// Created by mohammad on 6/22/2017.
//

#ifndef MYCONTROLLER_VISUALIZER_H
#define MYCONTROLLER_VISUALIZER_H

#include "MainController.h"

class Visualizer {
public:
    MainController *controller;
    void runController(MainController *controller);
    Visualizer(int argc, char **argv);
    void display();
    void idle();
    virtual ~Visualizer();
};


#endif //MYCONTROLLER_VISUALIZER_H
