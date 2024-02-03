#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <memory>
#include "Renderer.h"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(Renderer::Width, Renderer::Height);
    glutCreateWindow("Raytracer");
    Renderer::Init();
    glutDisplayFunc(Renderer::Display);
    glutMainLoop();

    return 0;
}
