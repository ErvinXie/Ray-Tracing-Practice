//
// Created by 谢威宇 on 2019-06-12.
//

#ifndef RAY_TRACING_IN_A_WEEKEND_HITABLE_H
#define RAY_TRACING_IN_A_WEEKEND_HITABLE_H

#include "ray.h"
class material;

struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;


};

#endif //RAY_TRACING_IN_A_WEEKEND_HITABLE_H
