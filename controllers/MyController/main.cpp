//
// Created by mohammad on 6/25/2017.
//

#include "Visualizer.h"

int main(int argc, char** argv) {
    MainController mainController;
    Visualizer visualizer(argc, argv);
    visualizer.runController(&mainController);
    return 0;
}
