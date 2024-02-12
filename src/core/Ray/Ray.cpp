#include "Ray.h"

Ray::Ray(const Math::Vec3 &origin, const Math::Vec3 &direction) : Origin(origin), Direction(Math::Normalize(direction)) {}

Math::Vec3 Ray::At(float t) const
{
    return Origin + t * Direction;
}