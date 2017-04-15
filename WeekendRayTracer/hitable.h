//
//  object.h
//  WeekendRayTracer
//
//  Created by samson stannus on 2017-04-14.
//  Copyright (c) 2017 samson stannus. All rights reserved.
//

#ifndef WeekendRayTracer_object_h
#define WeekendRayTracer_object_h
#include "ray.h"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
