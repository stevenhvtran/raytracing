#include <iostream>
#include "ray.h"

vec3 colour(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);


//     std::cout << "\n" << unit_direction.y() << "\n";
//     std::cout << "\n" << (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0) << "\n";
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 1280;
    int ny = 720;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = ny-1; j>= 0; j--) {
        for (int i = 0; i < nx; i ++) {
            float u = float(i) / float(nx);  // Fraction of distance across x of image
            float v = float(j) / float (ny);  // Fraction of distance across y of image

            ray r(origin, lower_left_corner + u * horizontal + v * vertical);  // Line from origin to someplace
            vec3 col = colour(r);

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
