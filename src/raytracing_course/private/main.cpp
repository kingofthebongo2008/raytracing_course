// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <limits>
#include <random>

#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

static vec3 color(const ray& r, hitable* world)
{
    hit_record rec;

    if (world->hit(r, 0.0f, std::numeric_limits<float>::max(), rec ) )
    {
        auto n = rec.normal;
        return 0.5f *  vec3(n.x() + 1.0f, n.y() + 1.0f, n.z() + 1.0f);
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = (unit_direction.y() + 1.0f) * 0.5f;
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

static float rnd()
{
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

int32_t main(int32_t argc, char* argv[])
{
    int32_t nx = 1280;
    int32_t ny = 720;
    int32_t ns = 1;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner  (-2.0f, -1.0f, -1.0f);
    vec3 horizontal         (4.0f, 0.0f, 0.0f);
    vec3 vertical           (0.0f, 2.0f, 0.0f);
    vec3 origin             (0.0f, 0.0f, 0.0f);

    hitable* list[2];

    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);

    hitable_list* world = new hitable_list(list, 2);

    camera cam;

    for (int32_t j = ny - 1; j >= 0; j--)
    {
        for (int32_t i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);

            for (int32_t s = 0; s < ns; ++s)
            {
                float u = float( i + rnd()) / float(nx);
                float v = float( j + rnd()) / float(ny);

                ray r = cam.get_ray(u, v);

                col += color(r, world);
            }

            col /= ns;

            int32_t ir = int32_t(255.99 * col.r());
            int32_t ig = int32_t(255.99 * col.g());
            int32_t ib = int32_t(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}




