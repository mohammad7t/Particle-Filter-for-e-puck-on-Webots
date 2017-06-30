//
// Created by mohammad on 6/22/2017.
//

#include "Visualizer.h"
#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <ctime>

Visualizer *_singleton = NULL;

void _display() {
    cout << "display" << endl;
    if (_singleton) {
        _singleton->display();
    }
}

void _idle() {
    // cout << "idle" << endl;
    if (_singleton) {
        _singleton->idle();
    }
}

Visualizer::Visualizer(int argc, char **argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    doDisplay = false; // Do not display until Controller  and ParticleFilter are set
    glutDisplayFunc(_display);
    glutIdleFunc(_idle);
}

void Visualizer::display() {
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    if (!doDisplay) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glutSwapBuffers();
        return;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Red

    /**
    for (int i = 0; i < map->obstacles.size(); i++) {
        drawCell(map->obstacles[i].first, map->obstacles[i].second);
    }
     /**/

    /**/
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; ++j) {
            if (!map->canRobotBeAt(map->getCenterCell(i, j))) {
                drawCell(i, j);
            }
        }
    }
    /**/

    cout << particleFilter->particleSet.size() << endl;
    for (int i = 0; i < particleFilter->particleSet.size(); ++i) {
        Particle &particle = particleFilter->particleSet[i];
        glBegin(GL_TRIANGLES);
        glColor3f(0, 0, 1.0f); // Blue
        Point base = particle.position;
        double angle = particle.angle;
        const double a = map->unit * 2 / 3;
        const double b = 3 * a;
        Point rotator = unitAngle(angle - M_PI_2);
        vertexPoint(Point(a, 0) * rotator + base);
        vertexPoint(Point(0, b) * rotator + base);
        vertexPoint(Point(-a, 0) * rotator + base);
        glEnd();
    }

    glutSwapBuffers();
}

void Visualizer::drawCell(int row, int col) {
    Point base = map->unit * Point(col, map->height - 1 - row);
    glBegin(GL_QUADS);
    vertexPoint(base + Point(0, 0));
    vertexPoint(base + Point(0, map->unit));
    vertexPoint(base + Point(map->unit, map->unit));
    vertexPoint(base + Point(map->unit, 0));
    glEnd();
}

Visualizer::~Visualizer() {
}

void Visualizer::runController(IController *controller) {
    _singleton = this;
    this->controller = controller;
    glutMainLoop();
}

void Visualizer::idle() {
    if (this->controller) {
        glutPostRedisplay();
        this->controller->nextStep();
    }
}

void Visualizer::visualize(ParticleFilter *particleFilter) {
    this->particleFilter = particleFilter;
    this->map = particleFilter->map;

    cellSize = 5;
    glutReshapeWindow((int) (map->width * map->unit * cellSize), (int) (map->height * map->unit * cellSize));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0, map->width, 0, map->height);
    doDisplay = true; // start displaying
}

void Visualizer::runWithoutController() {
    runController(NULL);
}

Point Visualizer::convert(const Point &p) {
    //return p;
    return Point(2 * X(p) / map->realWidth - 1, 2 * Y(p) / map->realHeight - 1);
}

void Visualizer::vertexPoint(const Point &p) {
    // cout << p << endl;
    Point converted = convert(p);
    // cout << '!' << converted << endl;
    glVertex2d(X(converted), Y(converted));
}
