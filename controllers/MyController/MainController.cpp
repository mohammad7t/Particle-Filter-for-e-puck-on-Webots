#include "MainController.h"

MainController::MainController(ParticleFilter *particleFilter, double motionModelSpeed) : DifferentialWheels() {
    this->particleFilter = particleFilter;
    for (int i = 0; i < SENSORS; i++) {
        string deviceName = "ps" + string(1, char('0' + i));
        sensor[i] = getDistanceSensor(deviceName);
        sensor[i]->enable(TIME_STEP);
    }

    accelerometer = getAccelerometer("accelerometer");
    accelerometer->enable(TIME_STEP);

    enableEncoders(TIME_STEP);

    speed[0] = 100;
    speed[1] = 100;

    odometry = Odometry(this, motionModelSpeed);

    stepNumber = 0;
}

MainController::~MainController() {
}

void MainController::readSensorValues() {
    for (int i = 0; i < SENSORS; i++) {
        sensorValue[i] = sensor[i]->getValue();
    }
    accValue = accelerometer->getValues();

    odometry.update();
}

int rotdir=0;
int oldrotdir=0;
int MainController::nextStep() {
    stepNumber++;
    readSensorValues();
    /**
    for (int i = 0; i < SENSORS; i++) {
        cout << sensorValue[i] << ',';
    }
    cout << ',' << rotdir << odometry.a << ',' << odometry.d << endl;
    /**/
    if (stepNumber % 20 == 0 && (rotdir == 0 | rotdir == 3)) {
        return particleFilterStep();
    }
    if (sensorValue[0] > 2000 | sensorValue[1] > 1600 | sensorValue[7] > 2000 | sensorValue[6] > 1600) {

        if (sensorValue[2] - 200 > sensorValue[5]) {
            rotdir = 1;
        } else if (sensorValue[5] - 200 > sensorValue[2]) {
            rotdir = 2;
        } else if (rotdir == 0 | rotdir == 3) {
            rotdir = rand() % 2 + 1;
        }
    }

    if (sensorValue[7] < 2000 && sensorValue[0] < 2000 && sensorValue[1] < 1600 && sensorValue[6] < 1600) {
        rotdir = 0;

        if (sensorValue[7] > 1000 | sensorValue[0] > 1000) {
            rotdir = 3;
        }
    }
    if (rotdir == 0) {
        speed[0] = 100;
        speed[1] = 100;
    } else if (rotdir == 3) {
        speed[0] = 50;
        speed[1] = 50;
    } else if (rotdir == 1) {
        speed[0] = -20;
        speed[1] = 20;
    } else if (rotdir == 2) {
        speed[0] = 20;
        speed[1] = -20;
    }
    if(rotdir==3 && oldrotdir==0){
        oldrotdir = rotdir;
        return particleFilterStep();
    }
    if((rotdir==0 || rotdir==3) && (oldrotdir==1 || oldrotdir==2)){
        oldrotdir = rotdir;
        return particleFilterStep();
    }
    if(stepNumber%3==1)oldrotdir = rotdir;
    setSpeed(speed[0], speed[1]);
    return step(TIME_STEP);
}

int MainController::particleFilterStep() {
    setSpeed(0, 0);
    int ret = step(TIME_STEP);
    readSensorValues();
    Action action = odometry.getAction();
    cout << "line 1" << SHOW(action) << endl;
    particleFilter->updateParticleSetWithAction(&action);
    cout << "line 2" << endl;
    Observation observation = getObservation();
    cout << "line 3" << endl;
    particleFilter->updateWeights(observation);
    cout << "line 4" << endl;
    particleFilter->reSampling();
    cout << "line 5" << endl;
    return ret;
}

void MainController::run() {
    int t;
    do {
        t = nextStep();
    } while (t != -1);
}

Observation MainController::getObservation() {

    return particleFilter->sensorModel->sensorValuesToObservation(sensorValue);
}
