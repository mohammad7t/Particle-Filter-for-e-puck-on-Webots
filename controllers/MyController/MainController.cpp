#include "MainController.h"

MainController::MainController(): DifferentialWheels() {
    for (int i=0; i<SENSORS; i++) {
        string deviceName = "ps" + string(1, char('0'+i));
        sensor[i] = getDistanceSensor(deviceName);
        sensor[i] -> enable(TIME_STEP * 4);
    }

    accelerometer = getAccelerometer("accelerometer");
    accelerometer -> enable(TIME_STEP * 4);

    enableEncoders(TIME_STEP * 4);

    speed[0] = 0;
    speed[1] = 0;

    odometry = Odometry(this);
}

MainController::~MainController() {
}

void MainController::readSensorValues() {
    for (int i=0; i<SENSORS; i++) {
        sensorValue[i] = sensor[i]->getValue();
    }
    accValue = accelerometer->getValues();

    odometry.update();
    cout << odometry.d << ' ' << odometry.a << endl;
}

void MainController::loop() {
    for (int i=0; i<SENSORS; i++) {
        cout << sensorValue[i] << ' ';
    }
    speed[0] = 100;
    speed[1] = 100;
    cout << endl;
}

void MainController::run() {
    int stepReturnValue = 0;
    for (stepNumber = 0; stepReturnValue != -1; stepNumber++) {
        readSensorValues();
        loop();
        setSpeed(speed[0], speed[1]);
        stepReturnValue = step(TIME_STEP);
    }
    string s;
}


int main(int argc, char **argv) {
    MainController* controller = new MainController();
    controller->run();
    delete controller;
    return 0;
}
