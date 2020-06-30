//
// Created by stran on 29/6/20.
//

#ifndef RAYTRACING_AXIS_ALIGNED_BOUNDING_BOX_H
#define RAYTRACING_AXIS_ALIGNED_BOUNDING_BOX_H

#include "utility.h"

class aabb {
public:
    aabb() = default;

    aabb(const point3 &a, const point3 &b) {
        min_corner = a;
        max_corner = b;
    }

    point3 min() const { return min_corner; }

    point3 max() const { return max_corner; }

    inline bool hit(const ray &r, double tmin, double tmax) const {
        for (int axis = 0; axis < 3; axis++) {
            double invD = 1.0f / r.direction()[axis];
            double t0 = (min()[axis] - r.origin()[axis]) * invD;
            double t1 = (max()[axis] - r.origin()[axis]) * invD;
            // Swap t's if direction is negative
            if (invD < 0.0f) {
                std::swap(t0, t1);
            }
            // Clamp values
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;

            if (tmax <= tmin) {
                // If any axis bound isn't hit by the ray then the bounding box isn't hit
                return false;
            }
        }
        return true;
    }

public:
    point3 min_corner;
    point3 max_corner;
};

aabb surrounding_box(aabb box0, aabb box1) {
    point3 min_corner(fmin(box0.min().x(), box1.min().x()),
                      fmin(box0.min().y(), box1.min().y()),
                      fmin(box0.min().z(), box1.min().z()));

    point3 max_corner(fmin(box0.max().x(), box1.max().x()),
                      fmin(box0.max().y(), box1.max().y()),
                      fmin(box0.max().z(), box1.max().z()));

    return {min_corner, max_corner};
}

#endif //RAYTRACING_AXIS_ALIGNED_BOUNDING_BOX_H
