#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "Particle.h"
#include "common.h"
#include "Observation.h"
#include <set>
#include "Cell.h"

class Map {
public:
    int width;
    int height;
    double scale;
    double unit;
    double realWidth;
    double realHeight;

    vector<vector<bool> > mapVector;
    vector<pair<int, int> > obstacles;
    vector<vector<bool> > canBeAt;

    Map(void);

    ~Map(void);

    Cell point2cell(double x, double y); //convert continious to discrete
    Cell point2cell(const Point &point);

    Point cell2point(int x, int y);//convert discrete to continious
    Point getCenterCell(const Cell &cell);


    bool isObstacle(double x,
                    double y); //parameter : real position x and y then compute cell that contain this position then return is it obstacle or not
    double distanceToNearestObstacle(Point pos, double angle);

    void readEnviroment();

    void readMapFile();


    void assignCanBeAt();

    Particle generateRandomParticle();
    bool canRobotAt(double d, double d1);

    bool canRobotAt(const Point &point);
};

