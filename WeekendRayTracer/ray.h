//
//  ray.h
//  WeekendRayTracer
//
//  Created by samson stannus on 2017-04-14.
//  Copyright (c) 2017 samson stannus. All rights reserved.
//

#ifndef WeekendRayTracer_ray_h
#define WeekendRayTracer_ray_h
#include "vec3.h"

class ray
{
public:
    ray() {}
    ray(const vec3& a, const vec3& b) { A = a; B = b; }
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + (t * B); }
    
    vec3 A;
    vec3 B;
    
};

#endif
