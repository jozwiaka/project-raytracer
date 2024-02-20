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
#include "MaterialDiffuseLight.h"
#include <tuple>

class Example
{
public:
    using Tuple = std::tuple<std::shared_ptr<Image>, std::shared_ptr<Camera>, std::shared_ptr<Scene>, std::shared_ptr<Renderer>>;

public:
    static Tuple SetUp(int id)
    {
        switch (id)
        {
        case 1:
            return ThreeSpheres(20, 10, 1000, 100);
        case 2:
            return RandomSpheres(20, 10, 1000, 100);
        case 3:
            return ThreeSpheres(500, 50, 1200, 1);
        case 4:
            return RandomSpheres(500, 50, 1200, 1);
        default:
            throw std::invalid_argument("Invalid scene ID.");
        }
    }

private:
    static Tuple ThreeSpheres(uint32_t numSamples, uint32_t maxDepth, uint32_t numThreads, uint32_t tileSize)
    {
        constexpr float aspectRatio = 16.0f / 9.0f;
        constexpr uint32_t width = 1200;
        auto image = std::make_shared<Image>(width, aspectRatio);

        constexpr auto cameraPosition = Vec3(0.0f, 0.0f, 0.0f);
        constexpr auto cameraTarget = Vec3(0.0f, 0.0f, -1.0f);
        constexpr auto cameraUpVector = Vec3(0.0f, 1.0f, 0.0f);
        constexpr float defocusAngle = 0.0f;
        constexpr float verticalFOV = 90.0f;
        constexpr float focusDist = 1.0f;
        auto camera = std::make_shared<Camera>(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, image);

        auto scene = std::make_shared<Scene>();
        auto materialGround = std::make_shared<MaterialLambertian>(Color(0.8f, 0.8f, 0.0f));
        auto materialCenter = std::make_shared<MaterialLambertian>(Color(0.7f, 0.3f, 0.3f));
#define METAL 1
#if METAL
        auto materialLeft = std::make_shared<MaterialMetal>(Color(0.8f, 0.8f, 0.8f), 0.0f);
        auto materialRight = std::make_shared<MaterialMetal>(Color(0.8f, 0.6f, 0.2f), 1.0f);
#else
        auto materialLeft = std::make_shared<MaterialDielectric>(1.5f);
        auto materialRight = std::make_shared<MaterialDielectric>(1.5f);
#endif
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, 0.0f, -1.0f), 0.5f, materialCenter));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, materialLeft));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(1.0f, 0.0f, -1.0f), 0.5f, materialRight));

        auto difflight = std::make_shared<MaterialDiffuseLight>(Color(4.0f, 4.0f, 4.0f));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, 5.0f, 0.0f), 2.0f, difflight));
        auto renderer = std::make_shared<Renderer>(image, camera, scene, numSamples, maxDepth, numThreads, tileSize);
        return std::make_tuple(image, camera, scene, renderer);
    }

    static Tuple RandomSpheres(uint32_t numSamples, uint32_t maxDepth, uint32_t numThreads, uint32_t tileSize)
    {
        constexpr float aspectRatio = 16.0f / 9.0f;
        constexpr uint32_t width = 1200;
        auto image = std::make_shared<Image>(width, aspectRatio);

        constexpr auto cameraPosition = Vec3(13.0f, 2.0f, 3.0f);
        constexpr auto cameraTarget = Vec3(0.0f, 0.0f, 0.0f);
        constexpr auto cameraUpVector = Vec3(0.0f, 1.0f, 0.0f);
        constexpr float defocusAngle = 0.6f;
        constexpr float verticalFOV = 20.0f;
        constexpr float focusDist = 10.0f;
        auto camera = std::make_shared<Camera>(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, image);

        auto scene = std::make_shared<Scene>();
        auto groundMat = std::make_shared<MaterialLambertian>(Color(0.5f, 0.5f, 0.5f));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, -1000, 0.0f), 1000, groundMat));
        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                auto chooseMat = Random::RandomFloat();
                Vec3 center(a + 0.9f * Random::RandomFloat(), 0.2f, b + 0.9f * Random::RandomFloat());

                if (Math::Length(center - Vec3(4.0f, 0.2f, 0.0f)) > 0.9f)
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
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
        auto material2 = std::make_shared<MaterialLambertian>(Color(0.4f, 0.2f, 0.1f));
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
        auto material3 = std::make_shared<MaterialMetal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
        scene->Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));
        auto renderer = std::make_shared<Renderer>(image, camera, scene, numSamples, maxDepth, numThreads, tileSize);
        return std::make_tuple(image, camera, scene, renderer);
    }
};