#include "TextureSolidColor.h"

TextureSolidColor::TextureSolidColor(const Color& c) : m_Col(c)
{
}

Color TextureSolidColor::Value(float u, float v, const Vec3 &p) const
{
    return m_Col;
}