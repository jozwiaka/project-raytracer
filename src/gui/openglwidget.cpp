
#include "OpenGLWidget.h"
#include <QDebug>

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

void OpenGLWidget::resizeGL(int width, int height)
{
    m_Renderer->ResizeViewport(width, height);
}

void OpenGLWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    resizeGL(event->size().width(), event->size().height());
}

void OpenGLWidget::paintGL()
{
    m_Renderer->Display();
}
