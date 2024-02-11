#pragma once

#include <limits>
#include <cmath>
#include <algorithm>

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

const Interval Interval::s_Empty = Interval(std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
const Interval Interval::s_Universe = Interval(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());