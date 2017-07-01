#include "MainController.h"

MainController::MainController(ParticleFilter *particleFilter) : DifferentialWheels() {
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

    odometry = Odometry(this);

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

int MainController::nextStep() {
    stepNumber++;
    readSensorValues();
    /*
    for (int i = 0; i < SENSORS; i++) {
        cout << sensorValue[i] << ',';
    }
    cout << endl;
     */

    if (stepNumber % 50 == 0) {

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
        speed[0] = 100;
        speed[1] = 100;
    }

    setSpeed(speed[0], speed[1]);
    return step(TIME_STEP);
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
