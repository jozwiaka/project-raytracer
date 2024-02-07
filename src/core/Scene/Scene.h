#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Ray.h"
#include <glm/glm.hpp>
#include "Material.h"
#include "Light.h"
class Scene
{
public:
    std::vector<std::unique_ptr<Object>> Objects;
    std::vector<std::unique_ptr<Light>> Lights;

public:
    void AddObject(std::unique_ptr<Object> object);
    void AddLight(std::unique_ptr<Light> light);
    bool Intersect(const Ray &ray, glm::vec3 &hitPoint, glm::vec3 &normal, Material &material) const;
};