#include "Object.h"

Object::Object(const Math::Point3 &center, const Math::Rotation3 &rotationDeg, std::shared_ptr<Material> material)
    : Center(center),
      RotationDeg(rotationDeg),
      Mat(material) {}
