#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "core.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <memory>
#include <QResizeEvent>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer, QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void paintGL() override;

private:
    std::shared_ptr<Image> m_Img;
    Camera m_Camera;
    Scene m_Scene;
    RendererOpenGL m_Renderer;
};

#endif // OPENGLWIDGET_H
