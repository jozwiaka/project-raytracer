#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Math.h"
#include "Material.h"
#include <memory>
#include "Color.h"
#include "MaterialLambertian.h"
#include "MaterialMetal.h"
#include "MaterialDielectric.h"
#include "Image.h"
#include "Random.h"
#include <memory>

class RaytracerWidget : public QWidget
{
public:
    RaytracerWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Set up the layout
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Create sliders for camera settings
        CreateSlider("Camera Position X", &cameraPosition.x, -20.0f, 20.0f, layout);
        CreateSlider("Camera Position Y", &cameraPosition.y, -20.0f, 20.0f, layout);
        CreateSlider("Camera Position Z", &cameraPosition.z, -20.0f, 20.0f, layout);

        CreateSlider("Camera Target X", &cameraTarget.x, -20.0f, 20.0f, layout);
        CreateSlider("Camera Target Y", &cameraTarget.y, -20.0f, 20.0f, layout);
        CreateSlider("Camera Target Z", &cameraTarget.z, -20.0f, 20.0f, layout);

        // Create button to trigger rendering
        renderButton = new QPushButton("Render", this);
        layout->addWidget(renderButton);
        connect(renderButton, &QPushButton::clicked, this, &RaytracerWidget::RenderScene);

        setLayout(layout);

        // Set up the initial camera and scene
        SetupCamera();
        SetupScene();
    }

private:
    QPushButton *renderButton;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Image> image;

    void CreateSlider(const QString &labelText, float *value, float minValue, float maxValue, QVBoxLayout *layout)
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

    void SetupCamera()
    {
        auto cameraPosition = Math::Vec3(13.0f, 2.0f, 3.0f);
        auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.0f);
        auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
        float defocusAngle = 0.6f;
        float verticalFOV = 20.0f;
        float focusDist = 10.0f;
        camera(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, &image);
    }

    void SetupScene()
    {
        // Set up the scene here as before
        // ...
    }

    void RenderScene()
    {
        // Render the scene using your Renderer class
        // ...
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    RaytracerWidget widget;
    widget.show();

    return app.exec();
}
