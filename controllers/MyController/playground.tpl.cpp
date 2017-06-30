#include "Visualizer.h"

Map map("env-s.txt", "map-s.txt");
SensorModel sensorModel("sensorMean-i.txt", "sensorVar.txt");
ParticleFilter particleFilter(10, &map, &sensorModel);

class Controller : public IController {
public:
    int nextStep() {
        cout << "here~~~~~~~~~~~" << endl;
        //double sensorValues[] = {15.0361, 48.8763, 57.569, 221.986, 235.146, 482.005, 107.171, 16.7376};
        double sensorValues[] = {15.0361, 10.8763, 10.569, 10.986, 10.146, 10.005, 10.171, 16.7376};
        Observation observation = particleFilter.sensorModel->sensorValuesToObservation(sensorValues);
        cout << observation << endl;
        particleFilter.updateWeights(observation);
        cout << "updated weights" << endl;
        particleFilter.reSampling();
        cout << "resampled" << endl;
        _sleep(2000);
        return 0;
    }
} controller;

int main(int argc, char **argv) {
    Visualizer visualizer(argc, argv);
    visualizer.visualize(&particleFilter);
    visualizer.runController(&controller);
    return 0;
}
