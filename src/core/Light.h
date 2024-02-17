#pragma once
#include "Math.h"
#include "Color.h"

class Light
{
public:
    Math::Vec3 Pos;

public:
    Light(const Math::Vec3 &position, const Color &color);

private:
    Math::Vec3 m_Col;
};