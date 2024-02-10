#include "Scene.h"

void Scene::AddObject(std::unique_ptr<Object> object)
{
    Objects.emplace_back(std::move(object));
}

void Scene::AddLight(std::unique_ptr<Light> light)
{
    Lights.emplace_back(std::move(light));
}

bool Scene::Intersect(const Ray &ray, Math::Point3 &hitPoint, Math::Vec3 &normal, Material &material) const
{
    float tClosest = std::numeric_limits<float>::infinity();
    bool hit = false;

    for (const auto &object : Objects)
    {
        float t;
        Math::Vec3 objectHitPoint, objectNormal;

        if (object->Intersect(ray, t, objectHitPoint, objectNormal) && t < tClosest)
        {
            tClosest = t;
            hit = true;

            hitPoint = objectHitPoint;
            normal = objectNormal;
            material = object->Mat;
        }
    }

    return hit;
}
