#pragma once

#include "vec3.h"

class ray
{
    public:
    ray() {}

    ray(const vec3& a, const vec3& b) : m_a(a), m_b(b) {}

    vec3 origin() const     { return m_a; }
    vec3 direction() const  { return m_b; }

    vec3 point_at_parameter(float t) const { return m_a + t * m_b; }

    vec3 m_a;
    vec3 m_b;
};

