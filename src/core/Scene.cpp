#include "Scene.h"
#include "MaterialLambertian.h"
#include "MaterialMetal.h"
#include "MaterialDielectric.h"
#include "ObjectSphere.h"
#include "ObjectCuboid.h"
#include "ObjectCylinder.h"

void Scene::AddObject(std::unique_ptr<Object> object)
{
    Objects.emplace_back(std::move(object));
}

void Scene::AddLight(std::unique_ptr<Light> light)
{
    Lights.emplace_back(std::move(light));
}

bool Scene::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    HitRecord tmpRec;
    bool hit = false;
    float tClosest = Math::Infinity();

    for (const auto &object : Objects)
    {
        if (object->Intersect(ray, Interval(ray_t.Min, tClosest), tmpRec))
        {
            hit = true;
            tClosest = tmpRec.t;
            rec = tmpRec;
        }
    }

    return hit;
}

void Scene::Default()
{
    auto groundMat = std::make_shared<MaterialLambertian>(Color(0.5f, 0.5f, 0.5f));
    AddObject(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, groundMat));
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
                    AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                }
                else if (chooseMat < 0.95f)
                {
                    // metal
                    auto albedo = Random::RandomVector(0.5f, 1.0f);
                    auto fuzz = Random::RandomFloat(0.0f, 0.5f);
                    sphereMat = std::make_shared<MaterialMetal>(albedo, fuzz);
                    AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                }
                else
                {
                    // glass
                    sphereMat = std::make_shared<MaterialDielectric>(1.5f);
                    AddObject(std::make_unique<ObjectSphere>(center, 0.2f, sphereMat));
                }
            }
        }
    }
    auto material1 = std::make_shared<MaterialDielectric>(1.5f);
    AddObject(std::make_unique<ObjectSphere>(Math::Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
    auto material2 = std::make_shared<MaterialLambertian>(Color(0.4f, 0.2f, 0.1f));
    AddObject(std::make_unique<ObjectSphere>(Math::Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
    auto material3 = std::make_shared<MaterialMetal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    AddObject(std::make_unique<ObjectSphere>(Math::Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));
}
