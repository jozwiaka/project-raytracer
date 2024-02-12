#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Math.h"
#include "Material.h"
#include <memory>
#include "Color.h"
#include "Lambertian.h"

int main()
{
    auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));

    auto cameraPosition = Math::Vec3(0.0f, 5.0f, 5.0f);
    auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.f);
    auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
    Camera camera(cameraPosition, cameraTarget, cameraUpVector);

    Scene scene;
    scene.BackgroundColor = Color();
    // scene.AddLight(std::make_unique<Light>(Math::Vec3(0.0f, 3.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 1.0f)));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, groundMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(-3.0f, 1.0f, 0.0f), 1.0f, groundMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, 2.0f, 0.0f), 2.0f, groundMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(3.0f, 1.0f, 0.0f), 1.0f, groundMaterial));
    // scene.AddObject(std::make_unique<Cylinder>(Math::Vec3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f, Math::Vec3(0.0f, 0.0f, 0.0f),groundMaterial));

    float aspectRatio = 16.0f / 9.0f;
    int width = 1200;
    int maxDepth = 20;
    Renderer renderer{&camera, &scene, width, aspectRatio, maxDepth};

    if (!renderer.Init())
    {
        return -1;
    }
    renderer.MainLoop();
}
