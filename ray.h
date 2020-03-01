//
// Created by stran on 1/3/20.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H
#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const vec3& origin, const vec3& direction) { _origin = origin; _direction = direction; }
    vec3 origin() const { return _origin; }
    vec3 direction() const { return _direction; }
    vec3 point_at_parameter(float scalar) const { return _origin + scalar * _direction; }

    vec3 _origin;
    vec3 _direction;
};

#endif //RAYTRACING_RAY_H
