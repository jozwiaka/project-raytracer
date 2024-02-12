#include "Interval.h"

Interval::Interval() : Min(Math::Infinity()), Max(-Math::Infinity()) {}

Interval::Interval(float min, float max) : Min(min), Max(max) {}

float Interval::Diff() const
{
    return Max - Min;
}

Interval Interval::Expand(float delta) const
{
    return Interval(Min - delta / 2, Max + delta / 2);
}

bool Interval::Contains(float x) const
{
    return Min <= x && x <= Max;
}

bool Interval::Surrounds(float x) const
{
    return Min < x && x < Max;
}

float Interval::Clamp(float x) const
{
    return std::clamp(x, Min, Max);
}

const Interval Interval::s_Empty = Interval(Math::Infinity(), -Math::Infinity());
const Interval Interval::s_Universe = Interval(-Math::Infinity(), Math::Infinity());