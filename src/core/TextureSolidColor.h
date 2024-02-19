#pragma once

#include "Texture.h"
#include "Math.h"

class TextureSolidColor : public Texture
{
public:
    TextureSolidColor() = default;
    TextureSolidColor(Color c);
    Color Value(float u, float v, const Vec3 &p) const override;

private:
    Color m_Col;
};