#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "rtweekend.h"


class camera {
public:
	/* RENDER TARGET */
	// Using ratio to have consistent resoulution
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 1920;

	void render(const hittable& world) {
		initalize();
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
private:
	int image_height;    // Rendered image height
	vec3 camera_center;         // Camera center
	vec3 pixel00_location;    // Location of pixel 0, 0
	vec3 pixel_delta_u;  // Offset to pixel to the right
	vec3 pixel_delta_v;  // Offset to pixel below

	void initalize() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		camera_center = vec3(0, 0, 0);

		// Determine viewport dimensions.
		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (double(image_width) / image_height);

		// Calculate the vectors across the horizontal and down the vertical viewport edges.
		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		// Calculate the horizontal and vertical delta vectors from pixel to pixel.
		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		// Calculate the location of the upper left pixel.
		auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	}


	color ray_color(const ray& r, const hittable& world) const {
		hit_record rec;
		if (world.hit(r, interval(0, std::numeric_limits<double>::infinity()), rec)) {
			return 0.5 * (rec.normal + color(1, 1, 1));
		}

		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};


#endif
