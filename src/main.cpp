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

int main()
{
    auto lambertian = std::make_shared<Lambertian>(Color(0.3, 0.3, 0.3));
    auto metal = std::make_shared<Metal>(Color(0.2, 0.2, 0.2), 0.5);
    auto dielectric = std::make_shared<Dielectric>(1.5);

    auto cameraPosition = Math::Vec3(0.0f, 5.0f, 5.0f);
    auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.f);
    auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
    Camera camera(cameraPosition, cameraTarget, cameraUpVector);

    Scene scene;
    scene.BackgroundColor = Color();
    // scene.AddLight(std::make_unique<Light>(Math::Vec3(0.0f, 3.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 1.0f)));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, lambertian));
    // scene.AddObject(std::make_unique<Sphere>(Math::Vec3(-4.0f, 2.0f, 0.0f), 2.0f, metal));
    // scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, 2.0f, 0.0f), 2.0f, dielectric));
    // scene.AddObject(std::make_unique<Sphere>(Math::Vec3(4.0f, 2.0f, 0.0f), 2.0f, metal));

    scene.AddObject(std::make_unique<Cylinder>(Math::Vec3(2.0f, 1.0f, 0.0f), 2.0f, 2.0f, Math::Vec3(0.0f, 0.0f, 0.0f), metal));
    scene.AddObject(std::make_unique<Cuboid>(Math::Vec3(-2.0f, 1.0f, 0.0f), Math::Vec3(2.0f, 2.0f, 2.0f), Math::Vec3(0.0f, 0.0f, 0.0f), metal));

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
