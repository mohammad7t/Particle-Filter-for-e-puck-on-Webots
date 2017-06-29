#include "Visualizer.h"

int main(int argc, char **argv) {
    Map map;
    SensorModel sensorModel;
    ParticleFilter particleFilter(100, &map, &sensorModel);
    MainController mainController(&particleFilter);

    Visualizer visualizer(argc, argv);
    visualizer.visualize(&particleFilter);
    visualizer.runController(&mainController);
    visualizer.runWithoutController();
    return 0;
}
