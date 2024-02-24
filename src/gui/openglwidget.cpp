
#include "OpenGLWidget.h"
#include <QDebug>

OpenGLWidget::OpenGLWidget(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer, QWidget *parent)
    : QOpenGLWidget(parent),
      m_Img(img), m_Camera(camera), m_Scene(scene), m_Renderer(renderer)
{
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::paintGL()
{
    m_Renderer.OnResize(width(), height());
    m_Camera.OnResize(width(), height());
    m_Renderer.Render(m_Camera, m_Scene);
}
