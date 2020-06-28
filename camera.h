//
// Created by stran on 24/6/20.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "utility.h"

class camera {
public:
    camera(point3 lookfrom, point3 lookat, vec3 vup, double vert_fov, double aspect_ratio) {
        double theta = degrees_to_radians(vert_fov);
        double h = tan(theta/2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;
        double focal_length = 1.0;

        // Vector in opposite direction we're looking
        vec3 w = unit_vector(lookfrom - lookat);
        // Orthogonal vector that is horizontal along plane of camera
        vec3 u = unit_vector(cross(vup, w));
        // Vector that is vertical along plane of camera
        vec3 v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }

    ray get_ray(double u, double v) const {
        return {origin, lower_left_corner + u * horizontal + v * vertical - origin};
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif //RAYTRACING_CAMERA_H
