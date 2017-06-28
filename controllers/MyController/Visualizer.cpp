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
    cout << "idle" << endl;
    if (_singleton) {
        _singleton->idle();
    }
}

Visualizer::Visualizer(int argc, char **argv) {
    FreeConsole();
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(_display);
    glutIdleFunc(_idle);
}

void Visualizer::display() {
    if (this->controller) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

        // Draw a Red 1x1 Square centered at origin
        glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(-0.5f, -0.5f * ((controller->stepNumber) % 3));    // x, y
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.7f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();

        glFlush();  // Render now
    }
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
