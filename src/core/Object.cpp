#include "Object.h"

Object::Object(const Math::Vec3 &center, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : Center(center),
      RotationDeg(rotationDeg),
      Mat(material) {}
