#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <memory>
#include "core.h"
#include "openglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer, QWidget *parent = nullptr);
    ~MainWindow();
    void Display();

private:
    std::shared_ptr<Ui::MainWindow> m_Ui;
    QVBoxLayout *m_Layout;
    QPushButton *m_RenderButton;
    OpenGLWidget *m_OpenGLWidget;
    std::shared_ptr<Image> m_Img;
    Camera m_Camera;
    Scene m_Scene;
    RendererOpenGL m_Renderer;

private:
    void CreateSlider(const QString &labelText, float *value, float minValue, float maxValue);
};

#endif // MAINWINDOW_H
