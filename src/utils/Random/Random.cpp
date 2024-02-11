#include "Random.h"
#include <random>
#include <limits>

float Random::RandomFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    return dis(gen);
}

float Random::RandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

Math::Vec3 Random::RandomVector()
{
    return Math::Vec3(RandomFloat(), RandomFloat(), RandomFloat());
}
Math::Vec3 Random::RandomVector(float min, float max)
{
    return Math::Vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
}

Math::Vec3 Random::RandomUnitVector()
{
    return Math::Normalize(Math::Vec3(RandomFloat(-1, 1), RandomFloat(-1, 1), RandomFloat(-1, 1)));
}