#include "Object.h"

Object::Object(const Vec3 &center, const Vec3 &rotationDeg, const Material &material)
    : Center(center),
      RotationDeg(rotationDeg),
      Substance(material) {}
