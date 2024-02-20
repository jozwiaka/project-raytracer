#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <tuple>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_Ui(std::make_unique<Ui::MainWindow>())
{
    m_Ui->setupUi(this);

    std::tie(m_Image, m_Camera, m_Scene, m_Renderer) = Example::ThreeSpheresTest();

    // Set up the m_Layout
    m_Layout = new QVBoxLayout(m_Ui->centralwidget);

    // Create sliders for camera settings
    // CreateSlider("Camera Position X", &m_Camera->Pos.x, -20.0f, 20.0f);
    // CreateSlider("Camera Position Y", &m_Camera->Pos.y, -20.0f, 20.0f);
    // CreateSlider("Camera Position Z", &m_Camera->Pos.z, -20.0f, 20.0f);

    // CreateSlider("Camera Target X", &m_Camera->Target.x, -20.0f, 20.0f);
    // CreateSlider("Camera Target Y", &m_Camera->Target.y, -20.0f, 20.0f);
    // CreateSlider("Camera Target Z", &m_Camera->Target.z, -20.0f, 20.0f);

    // Create button to trigger rendering
    m_RenderButton = new QPushButton("Display", this);
    m_Layout->addWidget(m_RenderButton);
    connect(m_RenderButton, &QPushButton::clicked, this, &MainWindow::Display);
    m_OpenGLWidget = new OpenGLWidget(m_Renderer, this);
    m_Layout->addWidget(m_OpenGLWidget);
}

void MainWindow::Display()
{
    m_OpenGLWidget->update();
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateSlider(const QString &labelText, float *value, float minValue, float maxValue)
{
    QLabel *label = new QLabel(labelText, this);
    m_Layout->addWidget(label);

    QSlider *slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(minValue * 100, maxValue * 100);
    slider->setValue((*value) * 100);
    m_Layout->addWidget(slider);

    connect(slider, &QSlider::valueChanged, this, [value, slider](uint32_t newValue)
            { *value = newValue / 100.0f; });
}
