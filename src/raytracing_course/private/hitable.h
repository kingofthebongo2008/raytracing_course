#pragma once

#include "vec3.h"
#include "ray.h"

class material;

struct hit_record
{
    float       t;
    vec3        p;
    vec3        normal;
    material*   material;
};

class hitable
{
    public:

    virtual bool hit(const ray& t, float t_min, float t_max, hit_record& rec) const = 0;
};



