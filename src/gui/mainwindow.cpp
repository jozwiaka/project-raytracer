#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_Ui(std::make_unique<Ui::MainWindow>())
{
    m_Ui->setupUi(this);
    constexpr float aspectRatio = 16.0f / 9.0f;
    constexpr int width = 1200;
    auto image = std::make_shared<Image>(width, aspectRatio);

    constexpr auto cameraPosition = Math::Vec3(13.0f, 2.0f, 3.0f);
    constexpr auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.0f);
    constexpr auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
    constexpr float defocusAngle = 0.6f;
    constexpr float verticalFOV = 20.0f;
    constexpr float focusDist = 10.0f;
    m_Camera = std::make_shared<Camera>(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, image);

    m_Scene = std::make_shared<Scene>();
    auto groundMat = std::make_shared<MaterialLambertian>(Color(0.5f, 0.5f, 0.5f));
    m_Scene->AddObject(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, groundMat));
    // for (int a = -11; a < 11; a++)
    // {
    //     for (int b = -11; b < 11; b++)
    //     {
    //         auto chooseMat = Random::RandomFloat();
    //         Math::Vec3 center(a + 0.9f * Random::RandomFloat(), 0.2f, b + 0.9f * Random::RandomFloat());

    //         if (Math::Length(center - Math::Vec3(4.0f, 0.2f, 0.0f)) > 0.9f)
    //         {
    //             std::shared_ptr<Material> sphereMat;

    //             if (chooseMat < 0.8f)
    //             {
    //                 // diffuse
    //                 auto albedo = Random::RandomVector() * Random::RandomVector();
    //                 sphereMat = std::make_shared<MaterialLambertian>(albedo);
    //                 m_Scene->AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
    //             }
    //             else if (chooseMat < 0.95f)
    //             {
    //                 // metal
    //                 auto albedo = Random::RandomVector(0.5f, 1.0f);
    //                 auto fuzz = Random::RandomFloat(0.0f, 0.5f);
    //                 sphereMat = std::make_shared<MaterialMetal>(albedo, fuzz);
    //                 m_Scene->AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
    //             }
    //             else
    //             {
    //                 // glass
    //                 sphereMat = std::make_shared<MaterialDielectric>(1.5f);
    //                 m_Scene->AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
    //             }
    //         }
    //     }
    // }
    auto material1 = std::make_shared<MaterialDielectric>(1.5f);
    m_Scene->AddObject(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
    auto material2 = std::make_shared<MaterialLambertian>(Color(0.4f, 0.2f, 0.1f));
    m_Scene->AddObject(std::make_unique<ObjectSphere>(Math::Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
    auto material3 = std::make_shared<MaterialMetal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    m_Scene->AddObject(std::make_unique<ObjectSphere>(Math::Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    constexpr int numSamples = 10;
    constexpr int maxDepth = 20;
    // unsigned int numThreads = std::thread::hardware_concurrency();
    constexpr unsigned int numThreads = 1000;
    constexpr int tileSize = 50;
    m_Renderer = std::make_shared<Renderer>(m_Camera, m_Scene, image, numSamples, maxDepth, numThreads, tileSize);

    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create sliders for camera settings
    CreateSlider("Camera Position X", &m_Camera->Pos.x, -20.0f, 20.0f, layout);
    CreateSlider("Camera Position Y", &m_Camera->Pos.y, -20.0f, 20.0f, layout);
    CreateSlider("Camera Position Z", &m_Camera->Pos.z, -20.0f, 20.0f, layout);

    CreateSlider("Camera Target X", &m_Camera->Target.x, -20.0f, 20.0f, layout);
    CreateSlider("Camera Target Y", &m_Camera->Target.y, -20.0f, 20.0f, layout);
    CreateSlider("Camera Target Z", &m_Camera->Target.z, -20.0f, 20.0f, layout);

    // Create button to trigger rendering
    m_RenderButton = new QPushButton("Render", this);
    // layout->addWidget(m_RenderButton);
    // connect(m_RenderButton, &QPushButton::clicked, this, &RaytracerWidget::RenderScene);
    OpenGLWidget *openGLWidget = new OpenGLWidget(m_Renderer, this);
    layout->addWidget(openGLWidget);

    setLayout(layout);

    // while (true)
    // {
    //     openGLWidget->paintGL();
    // }
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateSlider(const QString &labelText, float *value, float minValue, float maxValue, QVBoxLayout *layout)
{
    QLabel *label = new QLabel(labelText, this);
    layout->addWidget(label);

    QSlider *slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(minValue * 100, maxValue * 100);
    slider->setValue((*value) * 100);
    layout->addWidget(slider);

    connect(slider, &QSlider::valueChanged, this, [value, slider](int newValue)
            { *value = newValue / 100.0f; });
}
