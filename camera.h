//
// Created by 谢威宇 on 2019-06-12.
//

#ifndef RAY_TRACING_IN_A_WEEKEND_CAMERA_H
#define RAY_TRACING_IN_A_WEEKEND_CAMERA_H

#include "ray.h"

class camera {
public:
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 origin;
    glm::vec3 u, v, w;
    float lens_radius;

    camera() {
        lower_left_corner = glm::vec3(-2, -1, -1);
        horizontal = glm::vec3(4, 0, 0);
        vertical = glm::vec3(0, 2, 0);
        origin = glm::vec3(0, 0, 10);
    }

    camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vfov, float aspect) {

        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = glm::normalize(lookfrom - lookat);
        u = glm::normalize(glm::cross(vup, w));
        v = glm::cross(w, u);
        lower_left_corner = origin - half_width * u - half_height * v - w;
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
    }

    camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vfov, float aspect, float aperture,
           float focus_dist) {
        lens_radius = aperture / 2;
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = glm::normalize(lookfrom - lookat);
        u = glm::normalize(glm::cross(vup, w));
        v = glm::cross(w, u);
        lower_left_corner = origin - (half_width * u + half_height * v + w) * focus_dist;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    ray get_ray(float s, float t) {
        glm::vec3 rd = lens_radius * random_in_unit_disk();
        glm::vec3 offset = u * rd.x + v * rd.y;
        return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

};

#endif //RAY_TRACING_IN_A_WEEKEND_CAMERA_H
