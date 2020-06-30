//
// Created by stran on 24/6/20.
//

#ifndef RAYTRACING_UTILITY_H
#define RAYTRACING_UTILITY_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions

inline double degrees_to_radians(double degrees) {
    return (degrees / 180) * pi;
}

inline double random_double(double min, double max) {
    // Returns a random real in [min, max)
    std::mt19937 generator;
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

inline double random_double() {
    // Returns a random real in [0, 1).
    return random_double(0.0, 1.0);
}

inline int random_int(int min, int max) {
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common headers

#include "ray.h"
#include "vec3.h"
#include "material.h"

#endif //RAYTRACING_UTILITY_H
