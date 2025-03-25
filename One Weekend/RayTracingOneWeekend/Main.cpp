#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, std::numeric_limits<double>::infinity()), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}


int main() {

    /* RENDER TARGET */
    // Using ratio to have consistent resoulution
    auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;



    // Calculate the image height
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    hittable_list world;

    world.add(std::make_shared<sphere>(vec3(0, 0, -2), 0.5));
    world.add(std::make_shared<sphere>(vec3(0, 100.5, -1), 100));

    /* CAMERA */
    auto camera_center = vec3(0, 0, 0);
    auto focal_lenght = 1.0;
    // Calculate the viewport dimensions with the same techinque 
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    // Calculate the viewport's height, width diriractions
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    // Calculate delta pixel aka pixel representation on the vector space
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    // Calculate the corner where the first pixel will placed
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_lenght) - viewport_u / 2 - viewport_v / 2;
    // Calculate the exact postion of the first pixel
    auto pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Rendering
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << "" << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // next pixel location
            auto pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            auto pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone!\n";

}