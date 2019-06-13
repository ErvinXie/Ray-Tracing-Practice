//
// Created by 谢威宇 on 2019-06-12.
//

#ifndef RAY_TRACING_IN_A_WEEKEND_SCENE_H
#define RAY_TRACING_IN_A_WEEKEND_SCENE_H

#include "hitable_list.h"
#include "sphere.h"
#include "material.h"

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable *[n + 1];
    list[0] = new sphere(glm::vec3(0, -1000, 0), 1000, new lambertian(glm::vec3(0.5, 0.5, 0.5)));
    int i = 1;
    int num=7;
    for (int a = -num; a < num; a++) {
        for (int b = -num; b < num; b++) {
            float choose_mat = drand48();
            glm::vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if (glm::length(center - glm::vec3(4, 0, 0)) > 0.9) {
                if (choose_mat < 0.8) {
                    list[i++] = new sphere(center, 0.2, new lambertian(
                            glm::vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                } else if (choose_mat < 0.95) {
                    list[i++] = new sphere(center, 0.2,
                                           new metal(glm::vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()),
                                                               0.5 * (1 + drand48())), 0.5 * drand48()));
                } else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(glm::vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(glm::vec3(-4, 1, 0), 1.0, new lambertian(glm::vec3(0.4,0.2,0.1)));
    list[i++] = new sphere(glm::vec3(4, 1, 0), 1.0, new metal(glm::vec3(0.7,0.6,0.5),0));
    return new hitable_list(list,i);
}


#endif //RAY_TRACING_IN_A_WEEKEND_SCENE_H
