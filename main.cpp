#include "utility.h"

#include "hittable_list.h"
#include "sphere.h"
#include "color.h"

#include <iostream>


color ray_color(const ray &r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);
}

int main() {
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    double viewport_height = 9.0;
    double viewport_width = 16.0;
    double focal_length = 1.0;

    point3 origin(0, 0, 0);
    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(1, 1, -1), 0.5));
    world.add(make_shared<sphere>(point3(-1, 1, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            double u = double(i) / double(image_width);  // Fraction of distance across x of image
            double v = double(j) / double(image_height);  // Fraction of distance across y of image
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);  // Line from origin to someplace
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
