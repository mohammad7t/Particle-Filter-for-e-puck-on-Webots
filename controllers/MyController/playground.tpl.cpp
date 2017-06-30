#include "Visualizer.h"
#include "common.h"

vector<vector<double>> pathSensors;

Map map("env.txt", "map.txt");
SensorModel sensorModel("sensorMean-i.txt", "sensorVar-i.txt");
ParticleFilter particleFilter(10, &map, &sensorModel);

bool once = false;

class Controller : public IController {
public:
    int pathI;

    Controller() {
        pathI = 4;
    }

    double *nextSensorValues() {
        double *result = &(pathSensors[pathI][0]);
        pathI += 10;
        if (pathI >= pathSensors.size()) {
            pathI = pathSensors.size() - 100;
        }
        return result;
    }

    int nextStep() {

        Action action;
        action.distance = 5;
        action.rotateRadian = 0;
        particleFilter.updateParticleSetWithAction(&action);
        Observation observation = sensorModel.sensorValuesToObservation(nextSensorValues());
        LOG(observation);
        Particle &particle = particleFilter.particleSet[0];
        Map *world = particleFilter.map;
        Observation expectedObservation = sensorModel.getExpectedObservation(&particle, world);
        LOG(expectedObservation);
        particleFilter.updateWeights(observation);
        LOG(particleFilter.particleSet);
        /*
        cout << observation << endl;
        particleFilter.updateWeights(observation);
        cout << "updated weights" << endl;
        particleFilter.reSampling();
        cout << "resampled" << endl;
         */
        _sleep(1000);
        return 1;

    }
} controller;

int main(int argc, char **argv) {
    /**
    double sensorValues[] = {12.5719,53.7459,49.57,155.656,113.989,495.94,114.787,53.1823};
    Observation observation = particleFilter.sensorModel->sensorValuesToObservation(sensorValues);
    //cout << particleFilter.sensorModel->meanSensorVector << endl;
    cout << observation << endl;
    return 0;
    /**/

    ifstream fin("straight-path-sensors.txt");
    for (int i = 0; i < 700; i++) {
        vector<double> sensors;
        for (int j = 0; j < SENSORS; j++) {
            double value;
            fin >> value;
            sensors.push_back(value);
        }
        pathSensors.push_back(sensors);
    }

    cout << particleFilter.map->realWidth << endl;
    particleFilter.particleSet[0].position = Point(7.2, 7.2);
    particleFilter.particleSet[0].angle = M_PI_2;

    Visualizer visualizer(argc, argv);
    visualizer.visualize(&particleFilter);
    visualizer.runController(&controller);
    //visualizer.runWithoutController();
    return 0;
}
