#pragma once

#include <cstdint>
#include <math.h>

#include <iostream>

class vec3
{
    public:
    vec3() {}

    vec3(float e0, float e1, float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    float r() const { return e[0]; }
    float g() const { return e[1]; }
    float b() const { return e[2]; }
    
    const vec3& operator+() const { return *this; }
    const vec3  operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    float  operator[] (int32_t i) const { return e[i];}
    float& operator[] (int32_t i) { return e[i]; }

    vec3& operator+=(const vec3& o);
    vec3& operator-=(const vec3& o);
    vec3& operator*=(const vec3& o);
    vec3& operator/=(const vec3& o);

    vec3& operator*=(float t);
    vec3& operator/=(float t);

    float length() const
    {
        return sqrt( e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    float squared_length() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    void make_unit_vector();

    float e[3];
};

inline std::istream& operator>>(std::istream& is, vec3& t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& is, const vec3& t)
{
    is << t.e[0] << t.e[1] << t.e[2];
    return is;
}

inline vec3 operator+(const vec3& a, const vec3& b)
{
    return vec3( a.x() + b.x(), a.y() + b.y(), a.z() + b.z() );
}

inline vec3 operator-(const vec3& a, const vec3& b)
{
    return vec3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

inline vec3 operator*(const vec3& a, const vec3& b)
{
    return vec3(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
}

inline vec3 operator/(const vec3& a, const vec3& b)
{
    return vec3(a.x() / b.x(), a.y() / b.y(), a.z() / b.z());
}

inline vec3 operator*(const vec3& a, float t)
{
    return vec3(a.x() * t, a.y() * t, a.z() * t);
}

inline vec3 operator/(const vec3& a, float t)
{
    return vec3(a.x() / t, a.y() / t, a.z() / t);
}

inline vec3 operator*(float t, const vec3& a)
{
    return vec3(a.x() * t, a.y() * t, a.z() * t);
}

inline float dot(const vec3& a, const vec3& b)
{
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

inline vec3 cross(const vec3& a, const vec3& b)
{
    return vec3( 
                        a.y() * b.z() - a.z() * b.y(),
                   -(   a.x() * b.z() - a.z() * b.x()  ), 
                        a.x() * b.y() - a.y() * b.x()
               );
}

inline vec3& vec3::operator+=(const vec3& o)
{
    e[0] += o.e[0];
    e[1] += o.e[1];
    e[2] += o.e[2];

    return *this;
}

inline vec3& vec3::operator*=(const vec3& o)
{
    e[0] *= o.e[0];
    e[1] *= o.e[1];
    e[2] *= o.e[2];

    return *this;
}

inline vec3& vec3::operator/=(const vec3& o)
{
    e[0] /= o.e[0];
    e[1] /= o.e[1];
    e[2] /= o.e[2];

    return *this;
}

inline vec3& vec3::operator-=(const vec3& o)
{
    e[0] -= o.e[0];
    e[1] -= o.e[1];
    e[2] -= o.e[2];

    return *this;
}

inline vec3& vec3::operator*=(float o)
{
    e[0] *= o;
    e[1] *= o;
    e[2] *= o;

    return *this;
}

inline vec3& vec3::operator/=(float o)
{
    e[0] /= o;
    e[1] /= o;
    e[2] /= o;

    return *this;
}

inline void vec3::make_unit_vector()
{
    float k = 1.0f / length();

    e[0] *= k;
    e[1] *= k;
    e[1] *= k;
}

inline vec3 unit_vector(const vec3& v)
{
    return v / v.length();
}
