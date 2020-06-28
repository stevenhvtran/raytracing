//
// Created by stran on 25/6/20.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "ray.h"
#include "hittable.h"

class material {
public:
    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const = 0;
};

class lambertian : public material {
public:
    lambertian(const color &a) : albedo(a) {}

    virtual bool scatter(
            const ray &r, const hit_record &rec, color &attenuation, ray &scattered
    ) const {
        vec3 scattered_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scattered_direction);
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};

class metal : public material {
public:
    metal(const color &a) : albedo(a) {}

    virtual bool scatter(
            const ray &r, const hit_record &rec, color &attenuation, ray &scattered
    ) const {
        vec3 reflected = reflect(unit_vector(r.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
};

class fuzzy_metal : public material {
public:
    fuzzy_metal(const color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
    double fuzz;
};

double schlick(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class dielectric : public material {
public:
    dielectric(double ri) : ref_idx(ri) {}

    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const {
        attenuation = color(1.0, 1.0, 1.0);
        double etai_over_etat;
        if (rec.front_face) {
            etai_over_etat = 1.0 / ref_idx;
        } else {
            etai_over_etat = ref_idx;
        }

        vec3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
        if (etai_over_etat * sin_theta > 1.0) {
            // sin(theta)' cannot be > 1 so just reflect when it is (total internal reflection)
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        // Sometimes we reflect instead of refract depending on the angle and ref_idx
        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob) {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);
        return true;
    }

public:
    double ref_idx;
};

#endif //RAYTRACING_MATERIAL_H
