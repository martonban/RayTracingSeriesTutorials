#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "rtweekend.h"
#include "random_utils.h"
#include "material.h"

//-----------------------------------------------------------------------------
//                          Ray Tracing Tutorial - Camera
//
//-----------------------------------------------------------------------------



class camera {
public:
	// Default values, this will be overwritten by the presets on the main.cpp class
	// Must be public -> easier to code :)
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 1920;
	int samples_per_pixel = 10;
	int max_depth = 10;

	// This function will be the triggerd when we want to render an image
	void render(const hittable& world) {
		initalize();

		// Opening the file on the I/O stream (MUST HAVE)
		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		// Itarating every pixels + samples 
		for (int j = image_height - 1; j >= 0; j--) {
			// Progression debug text for the standard output
			std::cerr << "\rScanlines remaining: " << j << "" << std::flush;
			for (int i = 0; i < image_width; i++) {
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				write_color(std::cout, pixel_samples_scale * pixel_color);
			}
		}
		// Progression debug text for the standard output
		std::cerr << "\nDone!\n";
	}
private:
	int image_height;				// Rendered image height
	vec3 camera_center;				// Camera center
	vec3 pixel00_location;			// Location of pixel 0, 0
	vec3 pixel_delta_u;				// Offset to pixel to the right
	vec3 pixel_delta_v;				// Offset to pixel below
	double pixel_samples_scale;		// Color scale factor for a sum of pixel samples	


	// Before ray generation we have to calculate the private data members which are essential for ray generation
	void initalize() {
		// Image height calculation 
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		// AA realted 
		pixel_samples_scale = 1.0 / samples_per_pixel;

		camera_center = vec3(0, 0, 0);

		// Determine viewport dimensions
		auto focal_length = 1.0;															// Distance between camera pos and the viewport
		auto viewport_height = 2.0;															// [-1,1]
		auto viewport_width = viewport_height * (double(image_width) / image_height);		// adjusted [-1,1] 

		// Two direction vectors that define the horizontal and vertical axes of the viewport.
		// They determine the directions and scales for stepping across the viewport plane.
		// We use them to compute pixel positions starting from the top-left corner.
		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		// When we want to calculate the next pixel we have to know how much distance we need
		// to move in the virtual world to have an accurate ray direction. Both are directional vectors  
		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		// Calculate the exact location of the upper left pixel.
		auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	}

	// Ray Generation 
	ray get_ray(int i, int j) const {
		// Construct a camera ray originating from the origin and directed at randomly sampled
		// point around the pixel location i, j.
		auto offset = sample_square();
		auto pixel_sample = pixel00_location
			+ ((i + offset.x()) * pixel_delta_u)
			+ ((j + offset.y()) * pixel_delta_v);

		auto ray_origin = camera_center;
		auto ray_direction = pixel_sample - ray_origin;

		return ray(ray_origin, ray_direction);
	}

	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	vec3 sample_square() const {
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	// Calculate the pixel color only diffuse material
	color ray_color(const ray& r, int depth, const hittable& world) const {
		if (depth <= 0)
			return color(0, 0, 0);
		
		hit_record rec;
		if (world.hit(r, interval(0.001, std::numeric_limits<double>::infinity()), rec)) {
			ray scattered;
			color attenuation;
			if (rec.mat->scatter(r, rec, attenuation, scattered))
				return attenuation * ray_color(scattered, depth - 1, world);
			return color(0, 0, 0);
		}

		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};


#endif
