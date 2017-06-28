#include "Map.h"


Map::Map(void) {
    readEnviroment();
    readMapFile();
}

void Map::readEnviroment() {
    ifstream myFile;
    myFile.open("env.txt");

    if (myFile.is_open()) {
        myFile >> height >> width >> scale;

        myFile.close();
    }
}

void Map::readMapFile() {
    ifstream mapFile;
    mapFile.open("map.txt");
    cout << "reading map ...." << endl;

    if (mapFile.is_open()) {


        vector<bool> tempVector;
        mapArray = new bool *[height];
        for (int i = 0; i < height; i++) {
            string line;
            getline(mapFile, line);
            mapArray[i] = new bool[width];
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
                    mapArray[i][j] = true;
                    mapVector[i].push_back(true);
                    obstacles.push_back(pair<int, int>(j, i));
                    j += 1;
                } else if (line.at(index) == '0') {
                    mapArray[i][j] = false;
                    mapVector[i].push_back(false);
                    j += 1;
                }
                index += 1;

            }

        }
        mapFile.close();

    }
    cout << "read map finished" << endl;
    /*cout<<"mapVector size="<<mapVector.size()<<endl;
    cout<<"mapVector[0] size="<<mapVector.at(0).size()<<endl;
    */
    /*for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(mapArray[i][j])
                cout<<"1";
            else
                cout<<"0";
        }
        cout<<endl;
    }*/
}

bool Map::isObstacle(double x, double y) {
    int cellX = (int) (x / (1 / scale));
    int cellY = (int) (y / (1 / scale));
    for (int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].first == cellX && obstacles[i].second == cellY)
            return true;
    }
    return false;
}

double Map::distanceToNearestObstacle(Point pos, double angle, Map map) {
    double step = 0.1;
    double nextX, nextY;
    nextX = pos.real();
    nextY = pos.imag();

    int i = 0;
    while (true) {

        nextX = nextX + cos(angle) * step;
        nextY = nextY + sin(angle) * step;

        if (nextX < 0 || nextX > width * (1 / scale) || nextY < 0 || nextY > height * (1 / scale)) {
            return step * (i - 1);
        }
        if (map.isObstacle(nextX, nextY)) {
            return step * (i);
        }
        i += 1;
    }

}

Map::~Map(void) {
}
