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

static inline bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
    vec3 uv             = unit_vector(v);
    float dt            = dot(uv, n);
    float discriminant  = 1.0 - ni_over_nt * ni_over_nt * ( 1 - dt * dt);

    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}

static float schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);

    r0 = r0 * r0;

    return r0 + (1 - r0) * powf((1 - cosine), 5);
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
    vec3    albedo;
    float   fuzz;

    metal(vec3 a, float f) : albedo(a), fuzz(f) {}

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) override
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

        scattered = ray(rec.p, reflected + random_in_unit_sphere() * fuzz );
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0.0f;
    }
};

class dielectric : public material
{

public:
    float ref_idx;
    dielectric(float r) : ref_idx(r) {}

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) override
    {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);

        float ni_over_nt;
        attenuation = vec3(1.0, 1.0, 1.0);

        vec3    refracted;
        float   reflected_prob;
        float   cosine;

        if ( dot(r_in.direction(), rec.normal) > 0 )
        {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal ) / r_in.direction().length();
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }

        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
        {
            reflected_prob = schlick(cosine, ref_idx);
        }
        else
        {
            reflected_prob = 1.0;
        }

        if (rnd() < reflected_prob )
        {
            scattered = ray(rec.p, reflected);
        }
        else
        {
            scattered = ray(rec.p, refracted);
        }

        return true;
    }
};





