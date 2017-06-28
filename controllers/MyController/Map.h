#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<utility>
#include<vector>
#include "Particle.h"

using namespace std;

class Map {
public:
    Map(void);

    ~Map(void);

    bool isObstacle(double x,
                    double y); //parameter : real position x and y then compute cell that contain this position then return is it obstacle or not
    double distanceToNearestObstacle(Point pos, double angle, Map map);

private:
    int width;
    int height;
    int scale;

    bool **mapArray;
    vector<vector<bool>> mapVector;
    vector<pair<int, int>> obstacles;

    void readEnviroment();

    void readMapFile();

};

