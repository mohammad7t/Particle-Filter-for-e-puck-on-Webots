#include "Particle.h"
#include "Map.h"

Particle::~Particle(void) {

}

void Particle::doAction(Action *action, Map *world) {

    double step = 0.1;
    double nextX, nextY;
    nextX = position.real();
    nextY = position.imag();
    int iteration = (int) (action->distance / step);
//    cout<<"itearation ="<<iteration<<endl;
//    cout << "doAction: nextX=" << nextX << "\tnextY=" << nextY << endl;
//    cout << "can at here: "<<world->canRobotBeAt(nextX,nextY)<<endl;
    for (int j = 0; j < iteration; ++j) {

        nextX = nextX + cos(angle) * step;
        nextY = nextY + sin(angle) * step;
//        cout << "doAction: nextX=" << nextX << "\tnextY=" << nextY << endl;
        if (nextX < 0 || nextX > world->realWidth || nextY < 0 ||
            nextY > world->realHeight) {
            break;
        }
        if (!world->canRobotBeAt(nextX, nextY)) {
//            cout<<"conflict"<<endl;
            break;
        }
    }
    position = Point(nextX, nextY);
    angle = angle + action->rotateRadian;
}

Particle::Particle(void) {

}

ostream &operator<<(ostream &out, const Particle &particle) {
    out << particle.weight;
    return out;
}