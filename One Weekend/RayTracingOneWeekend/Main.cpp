#include <iostream>
#include "vec3.hpp"
#include "color.hpp"

int main() {

    // Image Resolution
    const int image_width = 1000;
    const int image_height = 1000;

    // Rendering
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << "" << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone!\n";

}