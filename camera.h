//
// Created by stran on 24/6/20.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "utility.h"

class camera {
public:
    camera(point3 lookfrom, point3 lookat, vec3 vup, double vert_fov, double aspect_ratio, double aperture,
           double focus_dist) {
        double theta = degrees_to_radians(vert_fov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;
        double focal_length = 1.0;

        // Vector in opposite direction we're looking
        w = unit_vector(lookfrom - lookat);
        // Orthogonal vector that is horizontal along plane of camera
        u = unit_vector(cross(vup, w));
        // Vector that is vertical along plane of camera
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        // Smaller aperture = less blurriness
        lens_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        // Select a random point on the lens to send rays from
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        return {origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset};
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};

#endif //RAYTRACING_CAMERA_H
