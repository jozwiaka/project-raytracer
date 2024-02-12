#pragma once

#include <limits>
#include <cmath>
#include <algorithm>
#include "Math.h"

class Interval
{
public:
    float Min, Max;
    static const Interval s_Empty, s_Universe;

public:
    Interval();
    Interval(float min, float max);
    float Diff() const;
    Interval Expand(float delta) const;
    bool Contains(float x) const;
    bool Surrounds(float x) const;
    float Clamp(float x) const;
};

const Interval Interval::s_Empty = Interval(Math::Infinity, -Math::Infinity);
const Interval Interval::s_Universe = Interval(-Math::Infinity, Math::Infinity);