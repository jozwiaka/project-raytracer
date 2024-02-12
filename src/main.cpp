#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Math.h"
#include "Material.h"
#include <memory>

int main()
{
    auto redMaterial = std::make_shared<Material>(Math::Vec3(1.0f, 0.0f, 0.0f));
    auto blueMaterial = std::make_shared<Material>(Math::Vec3(0.0f, 0.0f, 1.0f));

    auto cameraPosition = Math::Vec3(0.0f, 2.0f, 4.0f);
    auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.f);
    auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
    Camera camera(cameraPosition, cameraTarget, cameraUpVector);

    Scene scene;
    scene.BackgroundColor = Math::Vec3(0.0f, 0.0f, 0.0f);
    // scene.AddLight(std::make_unique<Light>(Math::Vec3(0.0f, 3.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 1.0f)));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, blueMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(-3.0f, 1.0f, 0.0f), 1.0f, redMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, 2.0f, 0.0f), 2.0f, redMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(3.0f, 1.0f, 0.0f), 1.0f, redMaterial));
    // scene.AddObject(std::make_unique<Cylinder>(Math::Vec3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f, Math::Vec3(0.0f, 0.0f, 0.0f), redMaterial));

    float aspectRatio = 16.0f / 9.0f;
    int width = 1200;
    int maxDepth = 10;
    Renderer renderer{&camera, &scene, width, aspectRatio, maxDepth};

    if (!renderer.Init())
    {
        return -1;
    }
    renderer.MainLoop();
}
