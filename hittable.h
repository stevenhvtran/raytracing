//
// Created by stran on 23/6/20.
//

#ifndef RAYTRACING_HITTABLE_H
#define RAYTRACING_HITTABLE_H

#include "utility.h"
#include "ray.h"
#include "axis_aligned_bounding_box.h"

class material;

struct hit_record {
    double t = infinity;
    vec3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(aabb& output_box) const = 0;
};

#endif //RAYTRACING_HITTABLE_H
