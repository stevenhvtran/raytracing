//
// Created by stran on 24/6/20.
//

#ifndef RAYTRACING_HITTABLE_LIST_H
#define RAYTRACING_HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    hittable_list() = default;
    explicit hittable_list(const shared_ptr<hittable>& object) { add(object); }

    void clear() {objects.clear();}
    void add(const shared_ptr<hittable>& object) {objects.push_back(object);}
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
public:
    std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const shared_ptr<hittable>& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif //RAYTRACING_HITTABLE_LIST_H
