#include "Material.h"

Material::Material(const Vec3 &color) : Color(color) {}
Material::Material(const Material &other) : Color(other.Color) {}