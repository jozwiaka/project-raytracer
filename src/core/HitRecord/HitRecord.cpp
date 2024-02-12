#include "HitRecord.h"

void HitRecord::SetFaceNormal(const Ray &ray, const Math::Vec3 &outwardNormal)
{
    FrontFace = Math::Dot(ray.Direction, outwardNormal) < 0;
    Normal = FrontFace ? outwardNormal : -outwardNormal;
}
