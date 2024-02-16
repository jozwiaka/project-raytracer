#include "core.h"

int main()
{
    float aspectRatio = 16.0f / 9.0f;
    int width = 1200;
    Image image(width, aspectRatio);

    auto cameraPosition = Math::Vec3(13.0f, 2.0f, 3.0f);
    auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.0f);
    auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
    float defocusAngle = 0.6f;
    float verticalFOV = 20.0f;
    float focusDist = 10.0f;
    Camera camera(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, &image);

    Scene scene;
    auto groundMat = std::make_shared<MaterialLambertian>(Color(0.5f, 0.5f, 0.5f));
    scene.AddObject(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, groundMat));
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto chooseMat = Random::RandomFloat();
            Math::Vec3 center(a + 0.9f * Random::RandomFloat(), 0.2f, b + 0.9f * Random::RandomFloat());

            if (Math::Length(center - Math::Vec3(4.0f, 0.2f, 0.0f)) > 0.9f)
            {
                std::shared_ptr<Material> sphereMat;

                if (chooseMat < 0.8f)
                {
                    // diffuse
                    auto albedo = Random::RandomVector() * Random::RandomVector();
                    sphereMat = std::make_shared<MaterialLambertian>(albedo);
                    scene.AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                }
                else if (chooseMat < 0.95f)
                {
                    // metal
                    auto albedo = Random::RandomVector(0.5f, 1.0f);
                    auto fuzz = Random::RandomFloat(0.0f, 0.5f);
                    sphereMat = std::make_shared<MaterialMetal>(albedo, fuzz);
                    scene.AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                }
                else
                {
                    // glass
                    sphereMat = std::make_shared<MaterialDielectric>(1.5f);
                    scene.AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                }
            }
        }
    }
    auto material1 = std::make_shared<MaterialDielectric>(1.5f);
    scene.AddObject(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
    auto material2 = std::make_shared<MaterialLambertian>(Color(0.4f, 0.2f, 0.1f));
    scene.AddObject(std::make_unique<ObjectSphere>(Math::Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
    auto material3 = std::make_shared<MaterialMetal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    scene.AddObject(std::make_unique<ObjectSphere>(Math::Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    int numSamples = 10;
    int maxDepth = 20;
    unsigned int numThreads = std::thread::hardware_concurrency();
    int tileSize = 400;
    Renderer renderer{&camera, &scene, &image, numSamples, maxDepth, numThreads, tileSize};

    if (!renderer.RenderLoop())
    {
        return -1;
    }
}