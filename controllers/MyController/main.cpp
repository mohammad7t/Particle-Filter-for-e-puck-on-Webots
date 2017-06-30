#include "MainController.h"
#include "Visualizer.h"

int main(int argc, char **argv) {
    ifstream fin("params.txt");
    int particleCount;
    fin >> particleCount;
    Map map("env.txt", "map.txt");
    SensorModel sensorModel("sensorMean-i.txt", "sensorVar-i.txt");
    ParticleFilter particleFilter(particleCount, &map, &sensorModel);
    Particle good;
    good.position = Point(6, 6);
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
