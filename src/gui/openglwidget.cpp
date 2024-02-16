
#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(std::shared_ptr<Renderer> renderer, QWidget *parent)
    : QOpenGLWidget(parent),
      m_Renderer(renderer)
{
    setMinimumSize(400, 400); // Set minimum size as needed
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_Renderer->ConfigureViewport();
}

// void OpenGLWidget::resizeGL(int w, int h)
// {
//     // Resize OpenGL viewport
//     glViewport(0, 0, w, h);
// }

void OpenGLWidget::paintGL()
{
    m_Renderer->Render();
}
