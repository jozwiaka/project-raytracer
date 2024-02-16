#include "Object.h"

Object::Object(const Math::Vec3 &center, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : m_Center(center),
      m_RotationDeg(rotationDeg),
      m_Mat(material) {}

std::shared_ptr<Material> Object::GetMaterial()
{
  return m_Mat;
}

void Object::Move(Math::Vec3 v)
{
  m_Center += v;
}
