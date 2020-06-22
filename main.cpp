#include <iostream>
#include "ray.h"

float sphere_discriminant(const vec3& center, float radius, const ray& r) {
    vec3 vector_to_center = r.origin() - center;  // We want this vector to start from where our ray did
    float a = dot(r.direction(), r.direction());
    float b = 2 * dot(vector_to_center, r.direction());
    float c = dot(vector_to_center, vector_to_center) - radius * radius;
    return b * b - 4 * a * c;
}

float hit_sphere(const vec3& center, float radius, const ray& r) {
    // x*x + y*y + z*z = r*r
    // If dot(p-c, p-c) = r*r, p is on the sphere
    // p(t) - c is the ray, if there exists t that satisfies above the ray hits sphere
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        // Use quadratic formula to solve for t, where p(t) - c is point on edge of sphere
        return (-b - sqrt(discriminant)) / 2.0 * a;
    }
}

vec3 colour(const ray& r) {
    // Vector (0, 0, -1) means the sphere is -1 in the z axis
    // Check if the ray hits the sphere of radius 0.5
    vec3 center(0, 0, -1);
    float t = hit_sphere(center, 0.9, r);
    if (t > 0.0) {
        // Ray hits the sphere
        // Get the unit normal vector that goes from the center of the sphere to ray hit sphere point
        vec3 N = unit_vector(r.point_at_parameter(t) - center);
        return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    } else {
        // Ray doesn't hit the sphere, shade as background
        vec3 unit_direction = unit_vector(r.direction());
        t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-t) * vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 1280;
    int ny = 720;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-8.0, -4.5, -0.55);
    vec3 horizontal(16.0, 0.0, 0.0);
    vec3 vertical(0.0, 9.0, 0.0);
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
