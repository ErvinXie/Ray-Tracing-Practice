//
// Created by 谢威宇 on 2019-06-12.
//

#ifndef RAY_TRACING_IN_A_WEEKEND_RAY_H
#define RAY_TRACING_IN_A_WEEKEND_RAY_H

#include "glm/glm.hpp"

class ray {

public:

    glm::vec3 origin, direction;

    ray() {}

    ray(const glm::vec3 &origin, const glm::vec3 &direction) : origin(origin), direction(direction) {}


    glm::vec3 point_at(float t) const {
        return origin + t * direction;
    }
};


#endif //RAY_TRACING_IN_A_WEEKEND_RAY_H
