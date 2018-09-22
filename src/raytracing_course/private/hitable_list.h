#pragma once

#include "hitable.h"

class hitable_list : public hitable
{
    public:
    hitable_list(hitable** h, int32_t count) : m_hitables(h), m_count(count) {}

    bool hit(const ray& t, float t_min, float t_max, hit_record& rec) const override;


    hitable** m_hitables;
    int32_t   m_count;
};


bool hitable_list::hit(const ray& t, float t_min, float t_max, hit_record& rec) const
{
    hit_record r;
    bool hit_something = false;
    double closest_so_far = t_max;


    for (auto i = 0; i < m_count; ++i)
    {
        if (m_hitables[i]->hit(t, t_min, closest_so_far, r))
        {
            hit_something   = true;
            closest_so_far  = r.t;
            rec = r;
        }
    }

    return hit_something;
}



