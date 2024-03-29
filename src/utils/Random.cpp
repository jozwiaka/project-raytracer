#include "Random.h"
#include <random>

float Random::RandomFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}

float Random::RandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

Vec3 Random::RandomVector()
{
    return Vec3(RandomFloat(), RandomFloat(), RandomFloat());
}
Vec3 Random::RandomVector(float min, float max)
{
    return Vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
}

Vec3 Random::RandomInUnitSphere()
{
    while (true)
    {
        auto p = RandomVector(-1.0f, 1.0f);
        if (Math::Dot(p, p) < 1.0f)
        {
            return p;
        }
    }
}

Vec3 Random::RandomUnitVector()
{
    return Math::Normalize(RandomInUnitSphere());
}

Vec3 Random::RandomOnHemisphere(const Vec3 &normal)
{
    auto onUnitSphere = RandomUnitVector();
    if (Math::Dot(onUnitSphere, normal) > 0.0f)
    {
        return onUnitSphere;
    }
    else
    {
        return -onUnitSphere;
    }
}

Vec3 Random::RandomInUnitDisk()
{
    while (true)
    {
        auto p = Vec3(RandomFloat(-1.0f, 1.0f), RandomFloat(-1.0f, 1.0f), 0.0f);
        if (Math::Dot(p, p) < 1.0f)
            return p;
    }
}
