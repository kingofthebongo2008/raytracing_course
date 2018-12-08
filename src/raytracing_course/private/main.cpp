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

#include <concrt.h>
#include <ppl.h>

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

static hitable_list* randomscene()
{
    int32_t n = 500;

    hitable** list = new hitable*[n + 1];

    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));

    int32_t i = 1;

    for (int32_t a = -11; a < 11; ++a)
    {
        for (int32_t b = -11; b < 11; ++b)
        {
            float choose_mat = rnd();

            vec3 center(a + 0.9 * rnd(), 0.2, b + 0.9*rnd());

            if ( (center - vec3(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(rnd()* rnd(), rnd()*rnd(), rnd()* rnd())));
                }
                else if (choose_mat < 0.95)
                {
                    list[i++] = new sphere(center, 0.2, new metal(vec3(0.5 * (1 + rnd()), 0.5 * (1 + rnd()), 0.5 * (1 + rnd())), 0.5 * (0 + rnd())));
                }
                else
                {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4,0.2,0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7,0.6,0.5), 0.0));

    return new hitable_list(list, i);
}

static void test()
{
    int32_t a, b, c, d, e;

    for (a = 0; a <= 9; ++a )
    for (b = 0; b <= 9; ++b)
    for (c = 0; c <= 9; ++c)
    for (d = 0; d <= 9; ++d)
    for (e = 0; e <= 9; ++e)
    {
        int32_t n1 = 0;
        int32_t n2 = 0;
            
        n1 += a * 10 * 10 * 10 * 10;
        n1 += b * 10 * 10 * 10;
        n1 += c * 10 * 10;
        n1 += d * 10;
        n1 += e;

        n2 += e * 10 * 10 * 10 * 10;
        n2 += d * 10 * 10 * 10;
        n2 += c * 10 * 10;
        n2 += b * 10;
        n2 += a;

        if ( n1 / 9 == n2 )
        {
            std::cout << n1 << std::endl;
        }
    }


    std::cout << "done" << std::endl;
}

int32_t main(int32_t argc, char* argv[])
{
    test();
    return 0;
    int32_t nx = 1920;
    int32_t ny = 1080;
    int32_t ns = 256;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner  (-2.0f, -1.0f, -1.0f);
    vec3 horizontal         (4.0f, 0.0f, 0.0f);
    vec3 vertical           (0.0f, 2.0f, 0.0f);
    vec3 origin             (0.0f, 0.0f, 0.0f);

    hitable* list[5];

    vec3 lookfrom(12, 12, 8);
    vec3 lookat(0, 0, -1);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 2.0f;

    camera cam(lookfrom, lookat, vec3( 0,1,0), 20.0f, float(nx) / float(ny), aperture, dist_to_focus);
    float r = cos(M_PI / 4);

    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8,0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));

    hitable_list* world = new hitable_list(list, 5);

    world = randomscene();

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




