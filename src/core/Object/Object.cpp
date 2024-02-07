#include "Object.h"

Object::Object(const glm::vec3 &center, const glm::vec3 &rotationDeg, const Material &material)
    : Center(center),
      RotationDeg(rotationDeg),
      Substance(material) {}
