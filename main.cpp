#include "utility.h"

#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"

#include <iostream>


color ray_color(const ray &r, const hittable &world, int depth) {
    if (depth <= 0)
        // Return black if ray bounce limit is reached
        return {0, 0, 0};

    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return {0, 0, 0};
    }
    vec3 unit_direction = unit_vector(r.direction());
    // Rays that point more upwards have higher blue intensity
    double t = 0.5 * (unit_direction.y() + 1.0);
    // Ranges from white (1, 1, 1) to (0.5, 0.7, 1.0) which is the full light blue colour
    return (1.0 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);
}

int main() {
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    camera cam(point3(-1, 1, 1), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);
    hittable_list world;

    // Middle sphere
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, make_shared<lambertian>(color(0.5, 0.5, 0.75))));
    // Right sphere
    world.add(make_shared<sphere>(point3(1.5, 0, -1), -0.45, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(point3(1.5, 0, -1), 0.5, make_shared<dielectric>(1.5)));
    // Left sphere
    world.add(make_shared<sphere>(point3(-1.5, 0, -1), 0.5, make_shared<fuzzy_metal>(color(0.75, 0.5, 0.5), 0.5)));
    // Large sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, make_shared<lambertian>(color(0.6, 0.75, 0.25))));

    for (int j = image_height - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);

            // Sample 100 random points around the pixel and combine colours
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u =
                        (i + random_double(-1.0, 1.0)) / (image_width - 1);  // Fraction of distance across x of image
                double v =
                        (j + random_double(-1.0, 1.0)) / (image_height - 1);  // Fraction of distance across y of image
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
