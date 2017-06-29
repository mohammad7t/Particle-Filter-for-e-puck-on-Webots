#include "Map.h"

Map::Map(const char *envFileName, const char *mapFileName) {
    readEnviroment(envFileName);
    readMapFile(mapFileName);
    assignCanBeAt();
}

void Map::readEnviroment(const char *envFileName) {
    ifstream myFile;
    myFile.open(envFileName);

    if (myFile.is_open()) {
        myFile >> height >> width >> scale;
        unit = 1 / scale;
        realWidth = unit * width;
        realHeight = unit * height;
        myFile.close();
    }
}

void Map::readMapFile(const char *mapFileName) {
    ifstream mapFile;
    mapFile.open(mapFileName);
    cout << "reading map ...." << endl;

    if (mapFile.is_open()) {


        vector<bool> tempVector;
        for (int i = 0; i < height; i++) {
            string line;
            getline(mapFile, line);
            tempVector.clear();
            mapVector.push_back(tempVector);
            int index = 0;
            int j = 0;
            int lineLength = line.length();
            while (index < lineLength) {
                //cout<<"index= "<<index<<endl;
                if (line.at(index) == ' ') {
                    index += 1;
                    continue;
                } else if (line.at(index) == '\n') {
                    break;
                } else if (line.at(index) == '1') {
                    mapVector[i].push_back(true);
                    obstacles.push_back(pair<int, int>(i, j));
                    j += 1;
                } else if (line.at(index) == '0') {
                    mapVector[i].push_back(false);
                    j += 1;
                }
                index += 1;

            }

        }
        mapFile.close();

    }
    cout << "read map finished" << endl;
}

bool Map::isObstacle(double x, double y) {
    Cell cell = point2cell(x, y);
    for (int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].first == cell.first && obstacles[i].second == cell.second)
            return true;
    }
    return false;
}

double Map::distanceToNearestObstacle(Point pos, double angle) {
    double step = 0.1;
    double nextX, nextY;
    nextX = pos.real();
    nextY = pos.imag();

    int i = 0;
    while (true) {
        // cout << "distanceToNearestObstacle: nextX=" << nextX << "\tnextY=" << nextY << endl;
        nextX = nextX + cos(angle) * step;
        nextY = nextY + sin(angle) * step;

        if (nextX < 0 || nextX > realWidth || nextY < 0 || nextY > realHeight) {
            return step * (i - 1);
        }
        if (isObstacle(nextX, nextY)) {
            return step * (i);
        }
        i += 1;
    }

}

Map::~Map(void) {
}

void Map::assignCanBeAt() {
    canBeAt = vector<vector<bool>>(height, vector<bool>(width, true));

    cout << "width=" << canBeAt[0].size() << endl;
    cout << "height=" << canBeAt.size() << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < obstacles.size(); k++) {
                if (abs(cell2point(i, j) - getCenterCell(obstacles[k])) < RADIUS_ROBOT) {
                    canBeAt[i][j] = false;
                    break;
                }
            }
        }
    }

}

Cell Map::point2cell(double x, double y) {
    int xx = (int) (x / unit);
    int yy = (int) (y / unit);
    return Cell(height - 1 - yy, xx);
}

Point Map::cell2point(int row, int col) {
    return unit * Point(col, height - row - 1);
}


bool Map::canRobotBeAt(double x, double y) {
    Cell centerCell = point2cell(x, y);
//    cout<<"canRobotBeAt: "<<centerCell.first<<","<<centerCell.second<<endl;
    return canBeAt[centerCell.first][centerCell.second];
}

Particle Map::generateRandomParticle() {
    Particle result;
    do {
        result.position = Point(randMToN(0, realWidth), randMToN(0, realHeight));
        result.angle = randMToN(0.0, 2 * M_PI);
    } while (!canRobotBeAt(result.position));
    return result;
}

Point Map::getCenterCell(const Cell &cell) {
    return cell2point(cell.first, cell.second);
}

Cell Map::point2cell(const Point &point) {
    return Cell(X(point), Y(point));
}

bool Map::canRobotBeAt(const Point &point) {
    return canRobotBeAt(X(point), Y(point));
}

Point Map::getCenterCell(int row, int col) {
    return getCenterCell(Cell(row, col));
}
