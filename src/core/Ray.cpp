#include "Ray.h"

Ray::Ray(const Vec3 &origin, const Vec3 &direction) : Origin(origin), Direction(Math::Normalize(direction)) {}

Vec3 Ray::At(float t) const
{
    return Origin + t * Direction;
}