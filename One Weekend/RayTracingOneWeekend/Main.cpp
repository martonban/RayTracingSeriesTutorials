#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "presets.h"


//-----------------------------------------------------------------------------
//                          Ray Tracing Tutorial - Main
//
//  Note this is a tutorial prpject based on the infamous Ray Tracing In a 
//  Weekend series. Thus all of this code is not created by me. 
// 
//  This is the entry point of the ray tracer.
//-----------------------------------------------------------------------------


int main() {
    // Scene setup and fill up with sphere geometry
    hittable_list world;
    auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(std::make_shared<sphere>(vec3(0.0, 100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<sphere>(vec3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(std::make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera (shooting rays from it)
    camera cam;
    
    // Image Presets
    enum Presets preset = FIDELITY;
    switch (preset) {
        case POOR:
            cam.aspect_ratio = 16.0 / 9.0;
            cam.image_width = 500;
            cam.samples_per_pixel = 100;
            cam.max_depth = 30;
            break;
        case PERFORMANCE:
            cam.aspect_ratio = 16.0 / 9.0;
            cam.image_width = 1000;
            cam.samples_per_pixel = 100;
            cam.max_depth = 40;
            break;
        case BALANCED:
            cam.aspect_ratio = 16.0 / 9.0;
            cam.image_width = 1920;
            cam.samples_per_pixel = 500;
            cam.max_depth = 50;
            break;
        case BEAUTY:
            cam.aspect_ratio = 16.0 / 9.0;
            cam.image_width = 1920;
            cam.samples_per_pixel = 1000;
            cam.max_depth = 50;
            break;
        case FIDELITY:
            cam.aspect_ratio = 16.0 / 9.0;
            cam.image_width = 3840;
            cam.samples_per_pixel = 1000;
            cam.max_depth = 100;
    }
    
    // Render the scene
    cam.render(world);
    return 0;
}