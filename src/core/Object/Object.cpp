#include "Object.h"

Object::Object(const Math::Point3 &center, const Math::Rotation3 &rotationDeg, std::shared_ptr<Material> material)
    : m_Center(center),
      m_RotationDeg(rotationDeg),
      m_Material(material) {}

std::shared_ptr<Material> Object::GetMaterial()
{
  return m_Material;
}
