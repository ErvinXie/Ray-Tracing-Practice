//
// Created by 谢威宇 on 2019-06-12.
//

#ifndef RAY_TRACING_IN_A_WEEKEND_SPHERE_H
#define RAY_TRACING_IN_A_WEEKEND_SPHERE_H

#include "hitable.h"

class sphere : public hitable {
public:
    glm::vec3 center;
    float radius;

    material* pMaterial;

    sphere() {}

    sphere(const glm::vec3 &center, float radius) : center(center), radius(radius) {}

    sphere(const glm::vec3 &center, float radius, material *matPtr): center(center), radius(radius),
                                                                     pMaterial(matPtr) {}

    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    glm::vec3 oc = r.origin - center;
    float a = glm::dot(r.direction, r.direction);
    float b = glm::dot(oc, r.direction);
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = pMaterial;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = pMaterial;
            return true;
        }
    }
    return false;
}

#endif //RAY_TRACING_IN_A_WEEKEND_SPHERE_H
