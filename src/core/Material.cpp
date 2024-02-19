#include "Material.h"

Material::Material(const Color &color) : Col(color) {}

Color Material::Emitted(float u, float v, const Vec3 &p) const
{
    return Color();
}
