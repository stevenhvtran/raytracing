#include "utility.h"

#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include "bvh.h"

#include <iostream>
#include <algorithm>
#include <execution>
#include <thread>

color ray_color(const ray &r, const hittable &world, int depth) {
    if (depth <= 0)
        // Return black if ray bounce limit is reached
        return {0, 0, 0};

    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return {0, 0, 0};
    }
    vec3 unit_direction = unit_vector(r.direction());
    // Rays that point more upwards have higher blue intensity
    double t = 0.5 * (unit_direction.y() + 1.0);
    // Ranges from white (1, 1, 1) to (0.5, 0.7, 1.0) which is the full light blue colour
    return (1.0 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);
}

void random_scene(hittable_list &world) {
    shared_ptr<material> material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    shared_ptr<material> material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    shared_ptr<material> material3 = make_shared<metal>(color(0.7, 0.6, 0.5));
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
}

void
compute_rows(std::vector<std::string> &data, camera &cam, bvh_node &world_tree, int rows_per_thread, int image_width,
             int image_height, int samples_per_pixel, int max_depth, int n) {

    std::string thread_data;

    int rows_start = n * rows_per_thread;
    int rows_end = (n + 1) * rows_per_thread;
    for (int j = rows_end - 1; j >= rows_start; j--) {
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);

            // Sample 100 random points around the pixel and combine colours
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u =
                        (i + random_double()) / (image_width - 1);  // Fraction of distance across x of image
                double v =
                        (j + random_double()) / (image_height - 1);  // Fraction of distance across y of image
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world_tree, max_depth);
            }

            write_color(thread_data, pixel_color, samples_per_pixel);
        }
    }
    data.at(n) = thread_data;
}

int main() {
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    const int max_depth = 50;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    point3 lookfrom = point3(13, 2, 3);
    point3 lookat = point3(0, 0, 0);
    vec3 vup(0, 1, 0);
    double dist_to_focus = 10;
    double aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    hittable_list world;
    random_scene(world);
    bvh_node world_tree = bvh_node(world, 0.001, infinity);

    const int num_threads = 12;
    const int rows_per_thread = image_height / num_threads;

    std::vector<int> n(num_threads);
    std::iota(std::begin(n), std::end(n), 0);
    std::vector<std::string> data(num_threads);

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        // Refactor this mess later
        threads.push_back(std::thread(compute_rows, std::ref(data), std::ref(cam), std::ref(world_tree), rows_per_thread, image_width, image_height,
                          samples_per_pixel, max_depth, i));
    }
    for (auto& t: threads) {
        t.join();
    }

    for (auto i = data.rbegin(); i != data.rend(); ++i)
        std::cout << *i;
}
