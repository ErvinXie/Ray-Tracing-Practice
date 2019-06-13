//
// Created by 谢威宇 on 2019-06-12.
//

#ifndef RAY_TRACING_IN_A_WEEKEND_HITABLE_LIST_H
#define RAY_TRACING_IN_A_WEEKEND_HITABLE_LIST_H

#include "hitable.h"

class hitable_list : public hitable {
public:
    hitable **list;
    int list_size;

    hitable_list() {}

    hitable_list(hitable **list, int listSize) : list(list), list_size(listSize) {}

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

};
bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_fat = t_max;
    for(int i=0;i<list_size;i++){
        if(list[i]->hit(r,t_min,closest_so_fat,temp_rec)){
            hit_anything = true;
            closest_so_fat = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //RAY_TRACING_IN_A_WEEKEND_HITABLE_LIST_H
