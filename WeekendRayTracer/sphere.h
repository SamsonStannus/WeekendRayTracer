//
//  sphere.h
//  WeekendRayTracer
//
//  Created by samson stannus on 2017-04-14.
//  Copyright (c) 2017 samson stannus. All rights reserved.
//

#ifndef WeekendRayTracer_sphere_h
#define WeekendRayTracer_sphere_h
#include "hitable.h"

class sphere: public hitable
{
public:
    sphere() {}
    sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 center;
    float radius;
    material *mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - (radius * radius);
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(b*b - a*c))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(b*b - a*c))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}
#endif