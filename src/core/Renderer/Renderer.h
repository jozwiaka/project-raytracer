#pragma once
#include <GL/glut.h>
class Renderer
{
public:
    static const int Width = 800;
    static const int Height = 600;

    static void Display()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        glEnd();
        glFlush();
    }

    static void Init()
    {
        glClearColor(0, 0, 0, 1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-1, 1, -1, 1);
    }
};