#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


int main() {

    hittable_list world;

    world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(vec3(0, 100.5, -1), 100));

    camera cam;
    
    
    bool is_test_settings = true;
    if (is_test_settings) {
        // Test Settings
        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 500;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;
    }
    else {
        // Relase Settings
        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 1920;
        cam.samples_per_pixel = 1000;
        cam.max_depth = 50;
    }
    
    cam.render(world);
    return 0;
}