//
// Created by stran on 24/6/20.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "utility.h"

class camera {
public:
    camera() {
        double aspect_ratio = 16.0 / 9.0;
        double viewport_height = 9.0;
        double viewport_width = 16.0;
        double focal_length = 10.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0, 0);
        vertical = vec3(0, viewport_height, 0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - point3(0, 0, focal_length);
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
