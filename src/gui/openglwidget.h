#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "Renderer.h"
#include <QOpenGLWidget>
#include <memory>

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(std::shared_ptr<Renderer> renderer, QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    // void resizeGL() override;
    void paintGL() override;

private:
    std::shared_ptr<Renderer> m_Renderer;
};

#endif // OPENGLWIDGET_H
