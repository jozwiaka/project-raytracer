
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
    // Initialize OpenGL state
    m_Renderer->Init();
}

// void OpenGLWidget::resizeGL(int w, int h)
// {
//     // Resize OpenGL viewport
//     glViewport(0, 0, w, h);
// }

void OpenGLWidget::paintGL()
{
    // Render OpenGL scene
    m_Renderer->Render();
}
