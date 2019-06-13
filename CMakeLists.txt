cmake_minimum_required(VERSION 3.14)
project(Ray_Tracing_in_a_weekend)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ray_Tracing_in_a_weekend main.cpp stb_image_write.h ray.h hitable.h sphere.h hitable_list.h camera.h material.h scene.h)