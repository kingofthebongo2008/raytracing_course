// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "ray.h"

static bool hit_sphere( const vec3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;

    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return discriminant > 0.0f;
}

static vec3 color(const ray& r)
{
    if (hit_sphere(vec3(0, 0, -1), 0.5, r))
    {
        return vec3(1.0, 0.0, 0.0);
    }

    vec3 unit_direction = unit_vector(r.direction());

    float t = (unit_direction.y() + 1.0f ) * 0.5f;
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int32_t main(int32_t argc, char* argv[])
{
    int32_t nx = 1920;
    int32_t ny = 1080;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner  (-2.0f, -1.0f, -1.0f);
    vec3 horizontal         (4.0f, 0.0f, 0.0f);
    vec3 vertical           (0.0f, 2.0f, 0.0f);
    vec3 origin             (0.0f, 0.0f, 0.0f);

    for (int32_t j = ny - 1; j >= 0; j--)
    {
        for (int32_t i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            vec3 col = color(r);

            int32_t ir = int32_t(255.99 * col.r());
            int32_t ig = int32_t(255.99 * col.g());
            int32_t ib = int32_t(255.99 * col.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}




