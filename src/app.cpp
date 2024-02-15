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
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Image.h"
#include "Random.h"

class RaytracerWidget : public QWidget
{
public:
    RaytracerWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Set up the layout
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Create sliders for camera settings
        createSlider("Camera Position X", &cameraPosition.x, -20.0f, 20.0f, layout);
        createSlider("Camera Position Y", &cameraPosition.y, -20.0f, 20.0f, layout);
        createSlider("Camera Position Z", &cameraPosition.z, -20.0f, 20.0f, layout);

        createSlider("Camera Target X", &cameraTarget.x, -20.0f, 20.0f, layout);
        createSlider("Camera Target Y", &cameraTarget.y, -20.0f, 20.0f, layout);
        createSlider("Camera Target Z", &cameraTarget.z, -20.0f, 20.0f, layout);

        // Create button to trigger rendering
        renderButton = new QPushButton("Render", this);
        layout->addWidget(renderButton);
        connect(renderButton, &QPushButton::clicked, this, &RaytracerWidget::renderScene);

        setLayout(layout);

        // Set up the initial camera and scene
        setupCamera();
        setupScene();
    }

private:
    Math::Vec3 cameraPosition;
    Math::Vec3 cameraTarget;
    QPushButton *renderButton;
    Camera camera;
    Scene scene;
    Image image;

    void createSlider(const QString &labelText, float *value, float minValue, float maxValue, QVBoxLayout *layout)
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

    void setupCamera()
    {
        float aspectRatio = 16.0f / 9.0f;
        int width = 1200;
        camera = Camera(cameraPosition, cameraTarget, Math::Vec3(0.0f, 1.0f, 0.0f), 0.6f, 20.0f, 10.0f, &image);
    }

    void setupScene()
    {
        // Set up the scene here as before
        // ...
    }

    void renderScene()
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
