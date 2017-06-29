//
// Created by mohammad on 6/22/2017.
//

#include "Visualizer.h"
#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

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
    cout << "here!!!" << endl;
    // FreeConsole();
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    doDisplay = false; // Do not display until Controller  and ParticleFilter are set
    glutDisplayFunc(_display);
    glutIdleFunc(_idle);
}

void Visualizer::display() {
    if (!doDisplay) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
        glFlush();  // Render now
        glutSwapBuffers();
        return;
    }

    //glClearColor(1.0f,1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            glBegin(GL_QUADS);
            if (map->mapVector[i][j]) {
                glColor3f(1.0f, 0.0f, 0.0f); // Red
            } else {
                glColor3f(1.0f, 1.0f, 1.0f); // white
            }

            Point base = map->unit * Point(map->width - 1 - j, i);
            vertexPoint(base + Point(0, 0));
            vertexPoint(base + Point(0, map->unit));
            vertexPoint(base + Point(map->unit, map->unit));
            vertexPoint(base + Point(map->unit, 0));
            glEnd();
            //break;
        }
        //break;
    }
    glFlush();  // Render now
    glutSwapBuffers();
}

Visualizer::~Visualizer() {
}

void Visualizer::runController(MainController *controller) {
    _singleton = this;
    this->controller = controller;
    glutMainLoop();
}

void Visualizer::idle() {
    if (this->controller) {
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
