#include "MaterialIsotropic.h"
#include "Random.h"

MaterialIsotropic::MaterialIsotropic(const Color &c) : Albedo(std::make_shared<TextureSolidColor>(c)) {}

MaterialIsotropic::MaterialIsotropic(std::shared_ptr<Texture> a) : Albedo(a) {}

bool MaterialIsotropic::Scatter(const Ray &ray, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const
{
    scattered = Ray(rec.Point, Random::RandomInUnitSphere());
    attenuation = Albedo->Value(rec.U, rec.V, rec.Point);
    return true;
}
