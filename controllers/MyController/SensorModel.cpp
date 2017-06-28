#include <cstdlib>
#include "SensorModel.h"

SensorModel::SensorModel(void) {
    readSensorModelFile();
    computeDistanceSensors();
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
            while (index < (int) (line.length())) {
                if (line.at(index) == ',') {
                    double x = atof(temp.c_str());
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
            stdDeviationSensorVector.push_back(tempVector);
            while (index < line.length()) {
                if (line.at(index) == ',') {
                    double x = atof(temp.c_str());
                    stdDeviationSensorVector[i].push_back(x);
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
        for (int i = 0; i < stdDeviationSensorVector.size(); i++) {
            cout << "sensor " << i << ": ";
            for (int j = 0; j < stdDeviationSensorVector[i].size(); j++) {
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

Observation SensorModel::sensorValuesToObservation(double *sensorValues) {
    return Observation();
}

double SensorModel::convertSingleSensorValue(int sensorId, double sensorValue) {
    return 0;
}

Gaussian SensorModel::getSensorGaussian(int sensorId, double distance) {
    Gaussian gaussian;
    gaussian.mean = distance;
    if (distance < 1) {
        gaussian.sigma2 = stdDeviationSensorVector[sensorId][0];
    } else if (distance > 7) {
        gaussian.sigma2 = stdDeviationSensorVector[sensorId][6];
    } else {
        gaussian.sigma2 = (distance - floor(distance)) * stdDeviationSensorVector[sensorId][floor(distance)]
                          + (ceil(distance) - distance) * stdDeviationSensorVector[sensorId][floor(distance) - 1];
    }
    cout<<"gausian s"<<sensorId<<" , "<<distance<<" = N("<<gaussian.mean<<","<<gaussian.sigma2<<")"<<endl;
    return gaussian;
}

void SensorModel::computeDistanceSensors() {
    distanceSensors = vector<vector<Gaussian>>(7, vector<Gaussian>(8, Gaussian(0, 0)));
    for (int i=0; i<SENSORS; i++){
        for (int j=0; j<7; j++){
            distanceSensors[j][i].mean = meanSensorVector[i][j];
            distanceSensors[j][i].sigma2 = pow(stdDeviationSensorVector[i][j], 2);
        }
    }
}
