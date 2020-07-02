//
// Created by stran on 23/6/20.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "vec3.h"

void write_color(std::string &out, color pixel_colour, int samples_per_pixel) {
    double r = pixel_colour.x();
    double g = pixel_colour.y();
    double b = pixel_colour.z();

    // Divide the color total by the number of samples and gamma-correct for gamma=2.0
    double scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out += std::to_string(static_cast<int>(255.99 * clamp(r, 0.0, 0.999))) + ' ' +
            std::to_string(static_cast<int>(255.99 * clamp(g, 0.0, 0.999))) + ' ' +
            std::to_string(static_cast<int>(255.99 * clamp(b, 0.0,0.999))) + '\n';
}

#endif //RAYTRACING_COLOR_H
