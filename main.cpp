#include "utility.h"

#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"

#include <iostream>


color ray_color(const ray &r, const hittable& world, int depth) {
    if (depth <= 0)
        return color(0, 0, 0);

    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        // Recurse by choosing the colour of a nearby point to the surface collision point
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);
}

int main() {
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    camera cam;
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -3), 0.5));
    world.add(make_shared<sphere>(point3(2, 0, -3), 0.5));
    world.add(make_shared<sphere>(point3(-2, 0, -3), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);

            // Sample 100 random points around the pixel and combine colours
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (i + random_double(-1.0, 1.0)) / (image_width - 1);  // Fraction of distance across x of image
                double v = (j + random_double(-1.0, 1.0)) / (image_height - 1);  // Fraction of distance across y of image
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
