
#include "OpenGLWidget.h"
#include <QDebug>

OpenGLWidget::OpenGLWidget(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer, QWidget *parent)
    : QOpenGLWidget(parent),
      m_Img(img), m_Camera(camera), m_Scene(scene), m_Renderer(renderer)
{
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_Renderer.ConfigureViewport();
}

void OpenGLWidget::resizeGL(int width, int height)
{
    m_Renderer.OnResize(width, height);
    m_Camera.OnResize(width, height);
}

void OpenGLWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    resizeGL(event->size().width(), event->size().height());
}

void OpenGLWidget::paintGL()
{
    m_Renderer.Render(m_Camera, m_Scene);
}
