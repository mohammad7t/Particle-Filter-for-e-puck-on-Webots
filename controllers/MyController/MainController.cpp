#include "MainController.h"

MainController::MainController() : DifferentialWheels() {
    for (int i = 0; i < SENSORS; i++) {
        string deviceName = "ps" + string(1, char('0' + i));
        sensor[i] = getDistanceSensor(deviceName);
        sensor[i]->enable(TIME_STEP * 4);
    }

    accelerometer = getAccelerometer("accelerometer");
    accelerometer->enable(TIME_STEP * 4);

    enableEncoders(TIME_STEP * 4);

    speed[0] = 0;
    speed[1] = 0;

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
    cout << odometry.d << ' ' << odometry.a << endl;
}

int MainController::nextStep() {
    stepNumber++;
    readSensorValues();
    for (int i = 0; i < SENSORS; i++) {
        cout << sensorValue[i] << ' ';
    }
    speed[0] = 100;
    speed[1] = 100;
    cout << endl;
    setSpeed(speed[0], speed[1]);
    return step(TIME_STEP);
}

void MainController::run() {
    int t;
    do {
        t = nextStep();
    } while (t != -1);
}
