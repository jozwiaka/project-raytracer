#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "Renderer.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <memory>
#include <QResizeEvent>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(std::shared_ptr<Renderer> renderer, QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeEvent(QResizeEvent *event) override;

private:
    std::shared_ptr<Renderer> m_Renderer;
};

#endif // OPENGLWIDGET_H
