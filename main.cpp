#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "glm/glm.hpp"

#include "ray.h"
#include "hitable.h"
#include "material.h"

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "scene.h"
#include <random>

const float EPS = 1e-3;



glm::vec3 color(const ray &r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, EPS, MAXFLOAT, rec)) {
        ray scattered;
        glm::vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return glm::vec3(0, 0, 0);
        }
    } else {
        glm::vec3 unit_direction = glm::normalize(r.direction);
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0f - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
    }
}
int main(int argc, char **argv) {
    int
            w = 1440,
            h = 720,
            n = 3,
            random_num = 100;

    unsigned char *data = new unsigned char[w * h * n];


    hitable *list[5];
    list[0] = new sphere(glm::vec3(0, 0, -1), 0.5, new lambertian(glm::vec3(0.8, 0.5, 0.5)));
    list[1] = new sphere(glm::vec3(0, -100.5, -1), 100, new lambertian(glm::vec3(0.8, 0.8, 0.8)));
    list[2] = new sphere(glm::vec3(1, 0, -1), 0.5, new metal(glm::vec3(0.8, 0.6, 0.2),0.3));
    list[3] = new sphere(glm::vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    list[4] = new sphere(glm::vec3(-1, 0, -1), -0.45, new dielectric(1.5));

//    hitable *world = new hitable_list(list,5);
    hitable *world = random_scene();


    glm::vec3 lookfrom(7,1.5,4.1);
    glm::vec3 lookat(4,1,2);
    float dist_to_focus = glm::length(lookfrom-lookat);
    float aperture=0.05f;
    camera cam(lookfrom,lookat,glm::vec3(0,1,0),40,w*1.0f/h,aperture,dist_to_focus+3);

    for (int i = 0; i < h; i++) {
        std::cout << 100.0 * i / h << "\t%" << std::endl;
        for (int j = 0; j < w; j++) {
            glm::vec3 col(0, 0, 0);
            for (int k = 0; k < random_num; k++) {
                float v = 1.0f * (h - i - drand48()) / h;
                float u = 1.0f * (j + drand48()) / w;
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= random_num;
            col = glm::vec3(sqrt(col.r), sqrt(col.g), sqrt(col.b));
            data[(i * w + j) * n + 0] = int(255.99 * col.r);
            data[(i * w + j) * n + 1] = int(255.99 * col.g);
            data[(i * w + j) * n + 2] = int(255.99 * col.b);
        }
    }
    stbi_write_png("test.png", w, h, n, data, 0);
    system("open test.png");
    stbi_image_free(data);

    return 0;
}