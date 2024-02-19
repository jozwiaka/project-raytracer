#include "Scene.h"
#include "MaterialLambertian.h"
#include "MaterialMetal.h"
#include "MaterialDielectric.h"
#include "ObjectSphere.h"
#include "ObjectCuboid.h"
#include "ObjectCylinder.h"

bool Scene::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    HitRecord tmpRec;
    bool hit = false;
    float tClosest = ray_t.Max;

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
