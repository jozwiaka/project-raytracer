#include "Scene.h"

void Scene::AddObject(std::unique_ptr<Object> object)
{
    Objects.push_back(std::move(object));
}

bool Scene::Intersect(const Ray &ray, Vec3 &hitPoint, Vec3 &normal, Material &material) const
{
    float tClosest = std::numeric_limits<float>::infinity();
    bool hit = false;

    for (const auto &object : Objects)
    {
        float t;
        Vec3 objectHitPoint, objectNormal;

        if (object->Intersect(ray, t, objectHitPoint, objectNormal) && t < tClosest)
        {
            tClosest = t;
            hit = true;

            hitPoint = objectHitPoint;
            normal = objectNormal;
            material = object->ObjMaterial;
        }
    }

    return hit;
}
