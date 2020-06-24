//
// Created by stran on 23/6/20.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_colour) {
    out << static_cast<int>(255.99 * pixel_colour.x()) << ' '
        << static_cast<int>(255.99 * pixel_colour.y()) << ' '
        << static_cast<int>(255.99 * pixel_colour.z()) << '\n';
}

#endif //RAYTRACING_COLOR_H
