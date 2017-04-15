//
//  main.cpp
//  WeekendRayTracer
//
//  Created by samson stannus on 2017-04-14.
//  Copyright (c) 2017 samson stannus. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"
#include "float.h"

vec3 color(const ray& r, hitable *world, int depth);

int main(int argc, const char * argv[]) {
    std::ofstream output("output.ppm");
    if (output.is_open()) {
        int nx = 1440;
        int ny = 900;
        int ns = 500;
        output << "P3\n" << nx << " " << ny << "\n255\n";
        hitable *list[5];
        list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.3, 0.8, 0.3)));
        list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.3, 0.3, 0.3)));
        list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.1));
        list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 1.0));
        list[4] = new sphere(vec3(0.5, -0.25, -0.5), 0.25, new dielectric(1.3));
        hitable *world = new hitable_list(list, 5);
        
        vec3 lookfrom(2,1,3);
        vec3 lookat(0,0,-1);
        float dist_to_focus = 4.0;
        float aperture = 0.1;
        
        camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);
        for (int j = ny - 1; j >= 0; j--) {
            for (int i = 0; i < nx; i++) {
                vec3 col(0, 0, 0);
                for (int s = 0; s < ns; s++) {
                    float u = float(i + drand48()) / float(nx);
                    float v = float(j + drand48()) / float(ny);
                    ray r = cam.get_ray(u, v);
                    col += color(r, world, 0);
                }
                col /= float(ns);
                col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
                int ir = int(255.99*col.r());
                int ig = int(255.99*col.g());
                int ib = int(255.99*col.b());
                output << ir << " " << ig << " " << ib << "\n";
            }
        }
        output.close();
        std::cout << "Finished writing file\n";
    }
    else {
        std::cout << "Could not open output.ppm\n";
    }
    return 0;
}

vec3 color(const ray& r, hitable *world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0  - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}