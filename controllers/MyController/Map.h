#pragma once


#include<iostream>
#include<fstream>
#include<string>
#include<utility>
#include<vector>
#include "Particle.h"
#include "common.h"
#include "Observation.h"
#include <set>

class Map {
public:
    int width;
    int height;
    double scale;
    bool **mapArray;

    vector<vector<bool> > mapVector;
    vector<pair<int, int> > obstacles;
    vector<vector<int > > canBeAt;

    Map(void);

    ~Map(void);

    bool isObstacle(double x,
                    double y); //parameter : real position x and y then compute cell that contain this position then return is it obstacle or not
    double distanceToNearestObstacle(Point pos, double angle    );
    void readEnviroment();
    void readMapFile();


    void assignCanBeAt();




};

