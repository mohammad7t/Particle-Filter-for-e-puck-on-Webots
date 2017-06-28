#include <cstdlib>
#include "SensorModel.h"


SensorModel::SensorModel(void) {
    readSensorModelFile();

}

void SensorModel::readSensorModelFile() {
    ifstream meanFile;
    meanFile.open("sensorMean.txt");
    cout << "reading mean file ..." << endl;
    if (meanFile.is_open()) {
        for (int i = 0; i < 8; i++) {
            string line;
            getline(meanFile, line);
            int index = 0;
            string temp = "";
            vector<double> tempVector;
            meanSensorVector.push_back(tempVector);
            while (index < (int)(line.length())) {
                if (line.at(index) == ',') {
                    double x = atof(temp.c_str());
                    cout << x << endl;
                    meanSensorVector[i].push_back(x);
                    temp = "";
                } else if (line.at(index) == '\n') {
                    break;
                } else {
                    temp += line.at(index);
                }
                index += 1;
            }

        }
        meanFile.close();
        cout << "read mean file finished" << endl;
        for (int i = 0; i < meanSensorVector.size(); i++) {
            cout << "sensor " << i << ": ";
            for (int j = 0; j < meanSensorVector[i].size(); j++) {

                cout << meanSensorVector[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "can not open mean file" << endl;
    }
    ifstream varianceFile;
    varianceFile.open("sensorVar.txt");
    cout << "reading variance file ..." << endl;
    if (varianceFile.is_open()) {
        for (int i = 0; i < 8; i++) {
            string line;
            getline(varianceFile, line);
            int index = 0;
            string temp = "";
            vector<double> tempVector;
            meanSensorVector.push_back(tempVector);
            while (index < line.length()) {
                if (line.at(index) == ',') {
                    double x = atof(temp.c_str());
                    cout << x << endl;
                    meanSensorVector[i].push_back(x);
                    temp = "";
                } else if (line.at(index) == '\n') {
                    break;
                } else {
                    temp += line.at(index);
                }
                index += 1;
            }

        }
        varianceFile.close();
        cout << "read variance file finished" << endl;
        for (int i = 0; i < meanSensorVector.size(); i++) {
            cout << "sensor " << i << ": ";
            for (int j = 0; j < meanSensorVector[i].size(); j++) {

                cout << stdDeviationSensorVector[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "can not open variance file" << endl;
    }
}

double SensorModel::calculateProbabilityObservation(Particle particle, Observation observ, Map map) {
    double p0 = 0.0;
    Point vec = ROBOT_RADIUS * exp(Point(0, S0_ORIENTATION));
    Point &point = particle.position;
    Point pos0 = point + vec;
    return 0.0;
}

double SensorModel::calculateSensorProbabilityObservation(Point point, double observ, Map map) {
    //map.distanceToNearestObstacle(pos0, S0_ORIENTATION - (M_PI / 2));
    return 0.0;
}

SensorModel::~SensorModel(void) {
}
