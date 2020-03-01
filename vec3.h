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
    vec3() = default;
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
    inline vec3& operator*=(float scalar);
    inline vec3& operator/=(float scalar);

    inline float length() const {
        return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    inline float squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    inline void make_unit_vector();

    float e[3]{};
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void vec3::make_unit_vector() {
    float k = 1 / std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
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

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]};
}

inline vec3 operator*(float scalar, const vec3 &v) {
    return {scalar * v.e[0], scalar * v.e[1], scalar * v.e[2]};
}

inline vec3 operator/(vec3 &v, float scalar) {
    return {v.e[0] / scalar, v.e[1] / scalar, v.e[2] / scalar };
}

inline vec3 operator*(const vec3 &v, float scalar) {
    return {scalar * v.e[0], scalar * v.e[1], scalar * v.e[2]};
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return {(v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
            -(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0]),
            (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0])};
}

inline vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(float scalar) {
    e[0] *= scalar;
    e[1] *= scalar;
    e[2] *= scalar;
    return *this;
}

inline vec3& vec3::operator/=(float scalar) {
    e[0] /= scalar;
    e[1] /= scalar;
    e[2] /= scalar;
    return *this;
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif //RAYTRACING_VEC3_H
