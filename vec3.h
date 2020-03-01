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
    vec3(float e0, float e1, float e2) { e[0] = e0; e[1]=e1; e[2] = e2; }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return {-e[0], -e[1], -e[2]}; }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline float length() const {
        return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    inline float squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    inline void make_unit_vector();

    float e[3]{};
};

#endif //RAYTRACING_VEC3_H
