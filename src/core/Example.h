#pragma once

#include <memory>
#include "utils.h"
#include "HitRecord.h"
#include "Ray.h"
#include "Image.h"
#include "Color.h"
#include "ColorManipulator.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "MaterialLambertian.h"
#include "MaterialMetal.h"
#include "MaterialDielectric.h"
#include "ObjectSphere.h"
#include "ObjectCuboid.h"
#include "ObjectCylinder.h"

class Example
{
public:
    static void Example_SimpleTest(std::shared_ptr<Image> &image, std::shared_ptr<Camera> &camera, std::shared_ptr<Scene> &scene, std::shared_ptr<Renderer> &renderer)
    {
        SetUpSimple(image, camera, scene);
        constexpr uint32_t numSamples = 100;
        constexpr uint32_t maxDepth = 50;
        constexpr uint32_t numThreads = 1000;
        constexpr uint32_t tileSize = 2;
        renderer = std::make_shared<Renderer>(image, camera, scene, numSamples, maxDepth, numThreads, tileSize);
    }

    static void Example_ComplexFinal(std::shared_ptr<Image> &image, std::shared_ptr<Camera> &camera, std::shared_ptr<Scene> &scene, std::shared_ptr<Renderer> &renderer)
    {
        SetUpComplex(image, camera, scene);
        constexpr uint32_t numSamples = 500;
        constexpr uint32_t maxDepth = 50;
        constexpr uint32_t numThreads = 1200;
        constexpr uint32_t tileSize = 1;
        renderer = std::make_shared<Renderer>(image, camera, scene, numSamples, maxDepth, numThreads, tileSize);
    }

    static void Example_ComplexTest(std::shared_ptr<Image> &image, std::shared_ptr<Camera> &camera, std::shared_ptr<Scene> &scene, std::shared_ptr<Renderer> &renderer)
    {
        SetUpComplex(image, camera, scene);
        constexpr uint32_t numSamples = 20;
        constexpr uint32_t maxDepth = 10;
        constexpr uint32_t numThreads = 1000;
        constexpr uint32_t tileSize = 20;
        renderer = std::make_shared<Renderer>(image, camera, scene, numSamples, maxDepth, numThreads, tileSize);
    }

private:
    static void SetUpSimple(std::shared_ptr<Image> &image, std::shared_ptr<Camera> &camera, std::shared_ptr<Scene> &scene)
    {
        constexpr float aspectRatio = 16.0f / 9.0f;
        constexpr uint32_t width = 1200;
        image = std::make_shared<Image>(width, aspectRatio);

        constexpr auto cameraPosition = Math::Vec3(0.0f, 0.0f, 0.0f);
        constexpr auto cameraTarget = Math::Vec3(0.0f, 0.0f, -1.0f);
        constexpr auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
        constexpr float defocusAngle = 0.0f;
        constexpr float verticalFOV = 90.0f;
        constexpr float focusDist = 1.0f;
        camera = std::make_shared<Camera>(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, image);

        scene = std::make_shared<Scene>();
        auto materialGround = std::make_shared<MaterialLambertian>(Color(0.8f, 0.8f, 0.0f));
        auto materialCenter = std::make_shared<MaterialLambertian>(Color(0.7f, 0.3f, 0.3f));
        auto materialLeft = std::make_shared<MaterialMetal>(Color(0.8f, 0.8f, 0.8f), 0.3f);
        auto materialRight = std::make_shared<MaterialMetal>(Color(0.8f, 0.6f, 0.2f), 1.0f);

        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, 0.0f, -1.0f), 0.5f, materialCenter));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(-1.0f, 0.0f, -1.0f), 0.5f, materialLeft));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(1.0f, 0.0f, -1.0f), 0.5f, materialRight));
    }

    static void SetUpComplex(std::shared_ptr<Image> &image, std::shared_ptr<Camera> &camera, std::shared_ptr<Scene> &scene)
    {
        constexpr float aspectRatio = 16.0f / 9.0f;
        constexpr uint32_t width = 1200;
        image = std::make_shared<Image>(width, aspectRatio);

        constexpr auto cameraPosition = Math::Vec3(13.0f, 2.0f, 3.0f);
        constexpr auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.0f);
        constexpr auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
        constexpr float defocusAngle = 0.6f;
        constexpr float verticalFOV = 20.0f;
        constexpr float focusDist = 10.0f;
        camera = std::make_shared<Camera>(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, image);

        scene = std::make_shared<Scene>();
        auto groundMat = std::make_shared<MaterialLambertian>(Color(0.5f, 0.5f, 0.5f));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, groundMat));
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
                        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                    }
                    else if (chooseMat < 0.95f)
                    {
                        // metal
                        auto albedo = Random::RandomVector(0.5f, 1.0f);
                        auto fuzz = Random::RandomFloat(0.0f, 0.5f);
                        sphereMat = std::make_shared<MaterialMetal>(albedo, fuzz);
                        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                    }
                    else
                    {
                        // glass
                        sphereMat = std::make_shared<MaterialDielectric>(1.5f);
                        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                    }
                }
            }
        }
        auto material1 = std::make_shared<MaterialDielectric>(1.5f);
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
        auto material2 = std::make_shared<MaterialLambertian>(Color(0.4f, 0.2f, 0.1f));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
        auto material3 = std::make_shared<MaterialMetal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Math::Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));
    }
};