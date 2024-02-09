#include "Object.h"

Object::Object(const Math::Point3 &center, const Math::Rotation3 &rotationDeg, const Material &material)
    : Center(center),
      RotationDeg(rotationDeg),
      Substance(material) {}
