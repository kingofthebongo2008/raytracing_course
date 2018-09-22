#pragma once
#include "hitable.h"

class sphere : public hitable
{
    public:

    sphere() = default;
    sphere( vec3 c, float r) : center(c), radius(r) {}

    bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;

    vec3    center;
    float   radius;
};

bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
    vec3 oc = r.origin() - center;

    float a = dot(r.direction(), r.direction());
    float b = dot(r.direction(), oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0.0f)
    {
        {
            float temp = (-b - sqrt(discriminant)) / a;

            if (temp > tmin && temp < tmax)
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                return true;
            }
        }

        {
            float temp = (-b + sqrt(discriminant)) / a;

            if (temp > tmin && temp < tmax)
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}






