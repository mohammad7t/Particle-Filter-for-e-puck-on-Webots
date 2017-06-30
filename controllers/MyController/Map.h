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

    Map(const char *envFileName, const char *mapFileName);

    ~Map(void);

    Cell point2cell(double x, double y); //convert continious to discrete
    Cell point2cell(const Point &point);

    Point cell2point(int x, int y);//convert discrete to continious
    Point getCenterCell(const Cell &cell);


    bool isObstacle(double x,
                    double y); //parameter : real position x and y then compute cell that contain this position then return is it obstacle or not
    double distanceToNearestObstacle(Point pos, double angle);

    void readEnviroment(const char *envFileName);

    void readMapFile(const char *mapFileName);

    void writeCanBeAtInFile();

    bool readCanBeAtFromFile();


    void assignCanBeAt();

    Particle generateRandomParticle();

    bool canRobotBeAt(double d, double d1);

    bool canRobotBeAt(const Point &point);

    Point getCenterCell(int row, int col);

};

