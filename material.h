//
// Created by 谢威宇 on 2019-06-12.
//

#ifndef RAY_TRACING_IN_A_WEEKEND_MATERIAL_H
#define RAY_TRACING_IN_A_WEEKEND_MATERIAL_H

#include "hitable.h"

class material {
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const = 0;
};

glm::vec3 random_in_unit_sphere() {
    glm::vec3 p;
    do {
        p = 2.0f * glm::vec3(drand48(), drand48(), drand48()) - glm::vec3(1, 1, 1);
    } while (glm::length(p) >= 1.0f);
    return p;
}
glm::vec3 random_in_unit_disk() {
    glm::vec3 p;
    do {
        p = 2.0f * glm::vec3(drand48(), drand48(), 0) - glm::vec3(1, 1,0);
    } while (glm::length(p) >= 1.0f);
    return p;
}


class lambertian : public material {
public:
    glm::vec3 albedo;

    lambertian(const glm::vec3 &a) : albedo(a) {}

    virtual bool
    scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const override {
        glm::vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
};

class metal : public material {
public:
    glm::vec3 albedo;
    float fuzz;

    metal(const glm::vec3 &albedo, float f) : albedo(albedo), fuzz(f) {
        if (fuzz > 1)
            fuzz = 1;
    }

    virtual bool
    scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const {
        glm::vec3 reflected = glm::reflect(glm::normalize(r_in.direction), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (glm::dot(scattered.direction, rec.normal) > 0);
    }
};

bool refract(const glm::vec3 &v, const glm::vec3 &n, float ni_over_nt, glm::vec3 &refracted) {
    glm::vec3 uv = glm::normalize(v);
    float dt = glm::dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float schlick(float cosine,float ref_idx){
    float r0 = (1-ref_idx)/(1+ref_idx);
    r0 = r0*r0;
    return r0+(1-r0)*pow((1-cosine),5);
}


class dielectric : public material {
public:
    float ref_idx;

    dielectric(float refIdx) : ref_idx(refIdx) {}

    bool scatter(const ray &r_in, const hit_record &rec, glm::vec3 &attenuation, ray &scattered) const override {
        glm::vec3 outward_normal;
        glm::vec3 reflected = glm::reflect(r_in.direction, rec.normal);
        float ni_over_nt;
        attenuation = glm::vec3(1, 1, 1);
        glm::vec3 refracted;
        float reflect_prob;
        float cosine;
        if (glm::dot(r_in.direction, rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx*glm::dot(r_in.direction,rec.normal)/glm::length(r_in.direction);
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -glm::dot(r_in.direction,rec.normal)/glm::length(r_in.direction);
        }
        if (refract(r_in.direction, outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine,ref_idx);
        } else {
            scattered = ray(rec.p, reflected);
            reflect_prob = 1.0;
        }

        if(drand48()<reflect_prob){
            scattered = ray(rec.p,reflected);
        }
        else{
            scattered = ray(rec.p,refracted);
        }
        return true;
    }
};

#endif //RAY_TRACING_IN_A_WEEKEND_MATERIAL_H
