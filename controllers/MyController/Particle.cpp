#include "Particle.h"
#include "Map.h"

Particle::~Particle(void) {

}

void Particle::doAction(Action action, Map *world) {
    if (action.isRotate) {

    } else {


        double step = 0.1;
        double nextX, nextY;
        nextX = position.real();
        nextY = position.imag();

        int iteration = (int) (action.amount / step);
        for (int j = 0; j < iteration; ++j) {
            cout << "distanceToNearestObstacle: nextX=" << nextX << "\tnextY=" << nextY << endl;
            nextX = nextX + cos(angle) * step;
            nextY = nextY - sin(angle) * step;

            if (nextX < 0 || nextX > world->width * (1 / world->scale) || nextY < 0 ||
                nextY > world->height * (1 / world->scale)) {
                break;
            }
            if (world->isObstacle(nextX, nextY)) {
                break;
            }
            position = Point(nextX, nextY);
        }
    }
}

Particle::Particle(void) {

}
