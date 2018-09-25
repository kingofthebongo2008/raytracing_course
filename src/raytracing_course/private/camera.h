#pragma once

#include "vec3.h"
#include "ray.h"
#define _USE_MATH_DEFINES
#include <math.h>

static vec3 random_in_unit_disk()
{
    vec3 p =vec3 (0,0,0);

    
    do
    {
        p = 2.0 * vec3(rnd(), rnd(), 0) - vec3(1, 1, 0);

    } while (dot(p, p) >= 1.0);
    
    return p;
}

class camera
{
    public:

    camera(vec3 lookfrom, vec3 lookat, vec3 up, float vfov, float aspect, float aperture, float focus_dist)
    {
        lens_radius = aperture / 2;
        float theta = vfov * M_PI / 180.0;
        float half_height = tanf(theta / 2.0);
        float half_width = aspect * half_height;

        origin = lookfrom;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(up, w));
        v = unit_vector(cross(w, u));

        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal        = 2 * half_width * focus_dist * u;
        vertical          = 2 * half_height * focus_dist * v;
    }

    ray get_ray(float s, float t)
    {
        vec3 rd     = lens_radius * random_in_unit_disk();
        vec3 offset = rd.x() * u + rd.y() * v;
        return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;
};



