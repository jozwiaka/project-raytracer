#include "Object.h"

Object::Object(const Math::Vec3 &center, const Math::Vec3 &rotationDeg, const Material &material)
    : Center(center),
      RotationDeg(rotationDeg),
      Substance(material) {}
