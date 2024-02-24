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

class Initializer
{
public:
    static void ThreeSpheresTest(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer) { ThreeSpheres(img, camera, scene, renderer, 20, 10); }

    static void RandomSpheresTest(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer) { RandomSpheres(img, camera, scene, renderer, 20, 10); }

    static void RandomSpheresFinal(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer) { RandomSpheres(img, camera, scene, renderer, 500, 50); }

private:
    static void ThreeSpheres(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer, uint32_t numSamples, uint32_t maxDepth)
    {
        constexpr float aspectRatio = 16.0f / 9.0f;
        constexpr uint32_t width = 1200;
        img = std::make_shared<Image>(width, aspectRatio);

        camera.Pos = Vec3(0.0f, 0.0f, 0.0f);
        camera.Target = Vec3(0.0f, 0.0f, -1.0f);
        camera.UpVector = Vec3(0.0f, 1.0f, 0.0f);
        camera.DefocusAngle = 0.0f;
        camera.VerticalFOV = 90.0f;
        camera.FocusDist = 1.0f;

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
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, 0.0f, -1.0f), 0.5f, materialCenter));
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, materialLeft));
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(1.0f, 0.0f, -1.0f), 0.5f, materialRight));

        auto difflight = std::make_shared<MaterialDiffuseLight>(Color(4.0f, 4.0f, 4.0f));
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, 5.0f, 0.0f), 2.0f, difflight));

        renderer.Img = img;
        renderer.NumSamples = numSamples;
        renderer.MaxDepth = maxDepth;
    }

    static void RandomSpheres(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer, uint32_t numSamples, uint32_t maxDepth)
    {
        constexpr float aspectRatio = 16.0f / 9.0f;
        constexpr uint32_t width = 1200;
        img = std::make_shared<Image>(width, aspectRatio);

        camera.Pos = Vec3(13.0f, 2.0f, 3.0f);
        camera.Target = Vec3(0.0f, 0.0f, 0.0f);
        camera.UpVector = Vec3(0.0f, 1.0f, 0.0f);
        camera.DefocusAngle = 0.6f;
        camera.VerticalFOV = 20.0f;
        camera.FocusDist = 10.0f;

        auto groundMat = std::make_shared<MaterialLambertian>(Color(0.5f, 0.5f, 0.5f));
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, -1000, 0.0f), 1000, groundMat));
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
                        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                    }
                    else if (chooseMat < 0.95f)
                    {
                        // metal
                        auto albedo = Random::RandomVector(0.5f, 1.0f);
                        auto fuzz = Random::RandomFloat(0.0f, 0.5f);
                        sphereMat = std::make_shared<MaterialMetal>(albedo, fuzz);
                        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                    }
                    else
                    {
                        // glass
                        sphereMat = std::make_shared<MaterialDielectric>(1.5f);
                        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                    }
                }
            }
        }
        auto material1 = std::make_shared<MaterialDielectric>(1.5f);
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
        auto material2 = std::make_shared<MaterialLambertian>(Color(0.4f, 0.2f, 0.1f));
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
        auto material3 = std::make_shared<MaterialMetal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
        scene.Objects.emplace_back(std::make_unique<ObjectSphere>(Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));

        renderer.Img = img;
        renderer.NumSamples = numSamples;
        renderer.MaxDepth = maxDepth;
    }
};