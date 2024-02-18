#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_Ui(std::make_unique<Ui::MainWindow>())
{
    m_Ui->setupUi(this);
    constexpr float aspectRatio = 16.0f / 9.0f;
    constexpr uint32_t width = 1200;
    auto image = std::make_shared<Image>(width, aspectRatio);

    constexpr auto cameraPosition = Math::Vec3(13.0f, 2.0f, 3.0f);
    constexpr auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.0f);
    constexpr auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
    constexpr float defocusAngle = 0.6f;
    constexpr float verticalFOV = 20.0f;
    constexpr float focusDist = 10.0f;
    m_Camera = std::make_shared<Camera>(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, image);

    m_Scene = std::make_shared<Scene>();
    m_Scene->SetUpExampleScene();

    constexpr uint32_t numSamples = 10;
    constexpr uint32_t maxDepth = 20;
    // uint32_t numThreads = std::thread::hardware_concurrency();
    constexpr uint32_t numThreads = 1000;
    constexpr uint32_t tileSize = 50;
    m_Renderer = std::make_shared<Renderer>(m_Camera, m_Scene, image, numSamples, maxDepth, numThreads, tileSize);

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
