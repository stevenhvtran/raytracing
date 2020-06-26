cmake_minimum_required(VERSION 3.15)
project(raytracing)

set(CMAKE_CXX_STANDARD 14)

add_executable(raytracing main.cpp vec3.h ray.h hittable.h sphere.h color.h hittable_list.h utility.h camera.h material.h)