#pragma once

#include "ray.h"
#include "hitable.h"
#include <random>

class material
{

    public:

    virtual bool scatter(const ray& in, const hit_record& r, vec3& attenuation, ray& scattered) = 0;
};


static inline float rnd()
{
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

static inline vec3 random_in_unit_sphere()
{
    vec3 p;

    do
    {
        p = 2.0 * vec3(rnd(), rnd(), rnd()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0f);
    return p;
}

static inline vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

class lambertian : public material
{
    public:
    vec3 albedo;

    lambertian ( vec3 a) : albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) override
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
};

class metal : public material
{
    public:
    vec3 albedo;

    metal(vec3 a) : albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) override
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }
};




