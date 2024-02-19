#include "Object.h"

Object::Object(const Vec3 &center, const Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : Center(center),
      RotationDeg(rotationDeg),
      Mat(material) {}
