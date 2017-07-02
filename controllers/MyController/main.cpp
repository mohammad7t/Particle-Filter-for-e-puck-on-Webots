#include "MainController.h"
#include "Visualizer.h"

int main(int argc, char **argv) {
    ifstream fin("params.txt");
    unsigned int particleCount;
    string envFile, mapFile, sensorMeanFile, sensorVarFile;
    double motionModelSpeed, dVar, aVar, thr, thrD;
    fin >> particleCount >> motionModelSpeed >> dVar >> aVar >> thr >> thrD;
    fin >> envFile >> mapFile >> sensorMeanFile >> sensorVarFile;
    Map map(envFile.c_str(), mapFile.c_str());
    SensorModel sensorModel(sensorMeanFile.c_str(), sensorVarFile.c_str());
    ParticleFilter particleFilter(particleCount, &map, &sensorModel);
    Particle good;
    good.position = Point(65, 7);
    good.angle = M_PI;
    //particleFilter.particleSet.push_back(good);
    MainController mainController(&particleFilter, motionModelSpeed, dVar, aVar, thr, thrD);
    //mainController.run();
    Visualizer visualizer(argc, argv);
    visualizer.visualize(&particleFilter);
    visualizer.runController(&mainController);
//    visualizer.runWithoutController();
    return 0;
}
