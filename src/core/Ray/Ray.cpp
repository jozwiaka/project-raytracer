#include "Ray.h"

Ray::Ray(const Vec3 &origin, const Vec3 &direction) : Origin(origin), Direction(direction.Normalize()) {}