#include "MainController.h"
#include "Visualizer.h"

int main(int argc, char **argv) {
    Map map("env.txt", "map.txt");
    SensorModel sensorModel("sensorMean-i.txt", "sensorVar-i.txt");
    ParticleFilter particleFilter(500, &map, &sensorModel);
    Particle good;
    good.position = Point(5, 5);
    good.angle = M_PI_2;
    particleFilter.particleSet.push_back(good);
    MainController mainController(&particleFilter);
    //mainController.run();
    Visualizer visualizer(argc, argv);
    visualizer.visualize(&particleFilter);
    visualizer.runController(&mainController);
//    visualizer.runWithoutController();
    return 0;
}
