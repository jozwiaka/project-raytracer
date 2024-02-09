#include "Ray.h"

Ray::Ray(const Math::Vec3 &origin, const Math::Vec3 &direction) : Origin(origin), Direction(Math::Normalize(direction)) {}