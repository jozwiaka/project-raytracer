#include "Scene.h"

void Scene::AddObject(std::unique_ptr<Object> object)
{
    Objects.push_back(std::move(object));
}

bool Scene::Intersect(const Ray &ray, Vec3 &hitPoint, Vec3 &normal, Material &material) const
{
    bool hit = false;

    return hit;
}
