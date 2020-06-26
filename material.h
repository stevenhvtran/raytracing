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

#endif //RAYTRACING_MATERIAL_H
