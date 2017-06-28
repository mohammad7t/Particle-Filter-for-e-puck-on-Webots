#pragma once

#include<vector>

using namespace std;

class Observation {
public:
    Observation(void);
    ~Observation(void);
    vector<double> physical;
    vector<double> theoretical;
};

