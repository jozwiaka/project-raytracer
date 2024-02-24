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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Display();

private:
    std::unique_ptr<Ui::MainWindow> m_Ui;
    QVBoxLayout *m_Layout;
    QPushButton *m_RenderButton;
    OpenGLWidget *m_OpenGLWidget;
    std::shared_ptr<Image> Img;
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<Scene> m_Scene;
    std::shared_ptr<Renderer> m_Renderer;

private:
    void CreateSlider(const QString &labelText, float *value, float minValue, float maxValue);
};

#endif // MAINWINDOW_H
