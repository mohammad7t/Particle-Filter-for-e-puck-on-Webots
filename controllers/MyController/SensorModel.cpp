#include <cstdlib>
#include "SensorModel.h"

SensorModel::SensorModel(const char *meanFilePath, const char *varFilePath) {
    readSensorModelFile(varFilePath, meanFilePath);
}

void SensorModel::readSensorModelFile(const char *s, const char *meanFilePath) {
    ifstream meanFile;
    meanFile.open(meanFilePath);
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
            double x = atof(temp.c_str());
            // cout << x << endl;
            meanSensorVector[i].push_back(x);
            temp = "";

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
    varianceFile.open(s);
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
                    stdDeviationSensorVector[i].push_back(pow(x, 2.0));
                    temp = "";
                } else if (line.at(index) == '\n') {

                    break;
                } else {
                    temp += line.at(index);
                }
                index += 1;
            }
            double x = atof(temp.c_str());
            cout << x << endl;
            stdDeviationSensorVector[i].push_back(x);
            temp = "";

        }
        varianceFile.close();
        cout << "read variance file finished" << endl;
        for (int i = 0; i < stdDeviationSensorVector.size(); i++) {
            cout << "sensor " << i << ": ";
            for (int j = 0; j < stdDeviationSensorVector[i].size(); j++) {
                cout << stdDeviationSensorVector[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "can not open variance file" << endl;
    }
}

SensorModel::~SensorModel(void) {
}

Observation SensorModel::sensorValuesToObservation(double *sensorValues) {
    Observation result(SENSORS, 0.0);
    for (int i = 0; i < SENSORS; i++) {
        result[i] = convertSingleSensorValue(i, sensorValues[i]);
    }
    return result;
}

double interpolate(double x1, double y1, double x2, double y2, double xQuery) {
    // cout << x1 << ' ' << y1 << ';' << x2 << ' ' << y2 << ';' << xQuery << endl;
    double dx = x2 - x1;
    return (xQuery - x1) / dx * y2 + (x2 - xQuery) / dx * y1;
}

double SensorModel::convertSingleSensorValue(int sensorId, double sensorValue) {
    vector<double> &means = meanSensorVector[sensorId];
    int slopeBegin = 0;

    for (; slopeBegin < DISTANCES - 2; slopeBegin++) {
        if (means[slopeBegin + 1] <= sensorValue) {
            break;
        }
    }

    return interpolate(means[slopeBegin], slopeBegin + 1,
                       means[slopeBegin + 1], slopeBegin + 2,
                       sensorValue);
}

Gaussian SensorModel::getSensorGaussian(int sensorId, double distance) {
    Gaussian gaussian;
    gaussian.mean = distance;
    if (distance <= 1) {
        gaussian.sigma2 = stdDeviationSensorVector[sensorId][0];
    } else if (distance >= 7 - 1e9) {
        gaussian.sigma2 = stdDeviationSensorVector[sensorId][6];
    } else {
        int lower = (int) floor(distance);
        int upper = (int) ceil(distance);
        if (lower == upper) {
            upper += 1;
        }
        gaussian.sigma2 = (distance - lower) * stdDeviationSensorVector[sensorId][upper]
                          + (upper - distance) * stdDeviationSensorVector[sensorId][lower];
    }
    if (gaussian.sigma2 < 0.0001) {
        cout << "===================================== " << distance << endl;
    }
//    cout << "gausian s" << sensorId << " , " << distance << " = N(" << gaussian.mean << "," << gaussian.sigma2 << ")"
//         << endl;
    return gaussian;
}

double SensorModel::getObservationProbability(Particle *particle, Observation *observation, Map *world) {
    double distanceSensor1 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S0_ORIENTATION);
    double distanceSensor2 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S1_ORIENTATION);
//    cout << "robot distance [" << X(particle->position) << "," << Y(particle->position) << ","
//         << particle->angle - M_PI / 2 + S1_ORIENTATION << "] =" << distanceSensor2;
    double distanceSensor3 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S2_ORIENTATION);
    double distanceSensor4 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S3_ORIENTATION);
    double distanceSensor5 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S4_ORIENTATION);
    double distanceSensor6 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S5_ORIENTATION);
    double distanceSensor7 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S6_ORIENTATION);
    double distanceSensor8 = world->distanceToNearestObstacle(particle->position,
                                                              particle->angle - M_PI / 2 + S7_ORIENTATION);

    double prob = getSensorGaussian(0, distanceSensor1).getProbability(observation[0][0]) *
                  getSensorGaussian(1, distanceSensor2).getProbability(observation[0][1]) *
                  getSensorGaussian(2, distanceSensor3).getProbability(observation[0][2]) *
                  getSensorGaussian(3, distanceSensor4).getProbability(observation[0][3]) *
                  getSensorGaussian(4, distanceSensor5).getProbability(observation[0][4]) *
                  getSensorGaussian(5, distanceSensor6).getProbability(observation[0][5]) *
                  getSensorGaussian(6, distanceSensor7).getProbability(observation[0][6]) *
                  getSensorGaussian(7, distanceSensor8).getProbability(observation[0][7]);

    return prob;
}