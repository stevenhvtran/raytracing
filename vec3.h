//
// Created by stran on 29/2/20.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <cmath>
#include <cstdlib>
#include <iostream>


class vec3 {
public:
    vec3() : e{0, 0, 0} {};

    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};

    double x() const { return e[0]; }

    double y() const { return e[1]; }

    double z() const { return e[2]; }

    vec3 operator-() const { return vec3{-e[0], -e[1], -e[2]}; }

    double operator[](int i) const { return e[i]; }

    double &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(const double t) {
        return *this *= 1 / t;
    }

    const vec3 &operator+() const { return *this; }

    double length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline static vec3 random() {
        return {random_double(), random_double(), random_double()};
    }

    inline static vec3 random(double min, double max) {
        return {random_double(min, max), random_double(min, max), random_double(min, max)};
    }

public:
    double e[3]{};
};

// Type aliases
using point3 = vec3;    // 3D point
using color = vec3;     // RGB color

// Utility functions

inline std::ostream &operator<<(std::ostream &os, const vec3 &t) {
    os << t.e[0] << ' ' << t.e[1] << ' ' << t.e[2];
    return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]};
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]};
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]};
}

inline vec3 operator*(double t, const vec3 &v) {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator*(const vec3 &v, double t) {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]};
}

inline vec3 operator/(const vec3 &v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3 &v1, const vec3 &v2) {
    return v1.e[0] * v2.e[0]
           + v1.e[1] * v2.e[1]
           + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return {(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
            -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
            (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])};
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 random_in_unit_sphere() {
    while(true) {
        vec3 p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    double a = random_double(0, 2 * pi);
    double z = random_double(-1, 1);
    double r = sqrt(1 - z*z);
    return {r*cos(a), r*sin(a), z};
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

#endif //RAYTRACING_VEC3_H
