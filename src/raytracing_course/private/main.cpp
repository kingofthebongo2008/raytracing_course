// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "ray.h"


vec3 color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());

    float t = (unit_direction.y() + 1.0f ) * 0.5f;
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int32_t main(int32_t argc, char* argv[])
{
    int32_t nx = 200;
    int32_t ny = 100;

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




