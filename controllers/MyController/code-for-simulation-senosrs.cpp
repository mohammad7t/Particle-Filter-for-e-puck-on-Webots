vector<double> values;

int MainController::nextStep() {
    setSpeed(0, 0);
    readSensorValues();
    double value = sensorValue[5];
    if (value > 2000) {
        cout << "Resetting!" << endl;
        values.clear();
    } else {
        values.push_back(value);
        int n = values.size();
        double mean = 0, var = 0;
        for (int i = 0; i < n; i++) {
            mean += values[i];
        }
        mean /= n;
        for (int i = 0; i < n; i++) {
            var += pow(mean - values[i], 2);
        }
        var = sqrt(var / n);
        cout << n << ' ' << mean << ' ' << var << endl;
    }
    cout << value << endl;
    return step(TIME_STEP);
}