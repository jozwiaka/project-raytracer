#include "Scene.h"

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
    HitRecord tempRec;
    bool hit = false;
    float tClosest = Math::Infinity;

    for (const auto &object : Objects)
    {
        if (object->Intersect(ray, Interval(ray_t.Min, tClosest), tempRec))
        {
            hit = true;
            tClosest = tempRec.t;
            rec = tempRec;
        }
    }

    return hit;
}
