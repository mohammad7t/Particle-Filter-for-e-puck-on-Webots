#include "MainController.h"
#include "Visualizer.h"

int main(int argc, char **argv) {
    Map map("env.txt", "map.txt");
    SensorModel sensorModel("sensorMean.txt", "sensorVar.txt");
    ParticleFilter particleFilter(1000, &map, &sensorModel);
    MainController mainController(&particleFilter);

    Visualizer visualizer(argc, argv);
    visualizer.visualize(&particleFilter);
    visualizer.runController(&mainController);
//    visualizer.runWithoutController();
    return 0;
}
