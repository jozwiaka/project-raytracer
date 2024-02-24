#include "RendererOpenGL.h"

RendererOpenGL::RendererOpenGL(const Renderer &renderer) : Renderer(renderer) {}

void RendererOpenGL::ConfigureViewport()
{
    glViewport(0, 0, Img->GetWidth(), Img->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Img->GetWidth(), Img->GetHeight(), 0, -1.0, 1.0); //(0,0) - top left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RendererOpenGL::OnResize(uint32_t width, uint32_t height)
{
    Renderer::OnResize(width, height);
    ConfigureViewport();
}

void RendererOpenGL::Render(const Camera &camera, const Scene &scene)
{
    Renderer::Render(camera, scene);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (uint32_t y = 0; y < Img->GetHeight(); ++y)
    {
        for (uint32_t x = 0; x < Img->GetWidth(); ++x)
        {
            glColor3f(Img->Data[y][x].x, Img->Data[y][x].y, Img->Data[y][x].z);
            glVertex2f(x, y);
        }
    }
    glEnd();
    glFlush();
}