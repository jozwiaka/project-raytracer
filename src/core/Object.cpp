#include "Object.h"

Object::Object(const Math::Vec3 &center, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : m_Center(center),
      m_RotationDeg(rotationDeg),
      m_Mat(material) {}

Math::Vec3 Object::GetCenter() const
{
  return m_Center;
}

void Object::SetCenter(const Math::Vec3 &center)
{
  m_Center = center;
}

Math::Vec3 Object::GetRotationDeg() const
{
  return m_RotationDeg;
}

void Object::SetRotationDeg(const Math::Vec3 &rotationDeg)
{
  m_RotationDeg = rotationDeg;
}

std::shared_ptr<Material> Object::GetMaterial() const
{
  return m_Mat;
}

void Object::SetMaterial(const std::shared_ptr<Material> &material)
{
  m_Mat = material;
}
