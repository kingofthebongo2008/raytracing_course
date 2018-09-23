// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <limits>
#include <random>

#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

static vec3 color(const ray& r, hitable* world, int depth)
{
    hit_record rec;

    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec ) )
    {
        ray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = (unit_direction.y() + 1.0f) * 0.5f;
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

int32_t main(int32_t argc, char* argv[])
{
    int32_t nx = 1280;
    int32_t ny = 720;
    int32_t ns = 256;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner  (-2.0f, -1.0f, -1.0f);
    vec3 horizontal         (4.0f, 0.0f, 0.0f);
    vec3 vertical           (0.0f, 2.0f, 0.0f);
    vec3 origin             (0.0f, 0.0f, 0.0f);

    hitable* list[4];

    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));

    hitable_list* world = new hitable_list(list, 4);

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

                col += color(r, world,0);
            }

            col /= ns;
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int32_t ir = int32_t(255.99 * col.r());
            int32_t ig = int32_t(255.99 * col.g());
            int32_t ib = int32_t(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}




