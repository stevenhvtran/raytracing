cmake_minimum_required(VERSION 3.15)
project(raytracing)

set(CMAKE_CXX_STANDARD 17)
add_executable(raytracing main.cpp vec3.h ray.h hittable.h sphere.h color.h hittable_list.h utility.h camera.h material.h axis_aligned_bounding_box.h bvh.h)
set (CMAKE_CXX_FLAGS "-pthread")
