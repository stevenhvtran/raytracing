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

hittable_list random_scene() {
    hittable_list world;

    shared_ptr<lambertian> ground_material = make_shared<lambertian>(color(0.6, 0.75, 0.25));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.4) {
                    // diffuse spheres
                    color albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.7) {
                    // metal spheres
                    color albedo = color::random(0.5, 1);
                    double fuzz = random_double(0.5, 1);
                    sphere_material = make_shared<fuzzy_metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass spheres
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    shared_ptr<material> material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    shared_ptr<material> material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    shared_ptr<material> material3 = make_shared<metal>(color(0.7, 0.6, 0.5));
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

int main() {
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    point3 lookfrom = point3(13, 2, 3);
    point3 lookat = point3(0, 0, 0);
    vec3 vup(0, 1, 0);
    double dist_to_focus = 10;
    double aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    hittable_list world = random_scene();

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
