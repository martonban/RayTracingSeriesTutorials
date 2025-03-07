#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "vec3.hpp"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	int rByte = int(255.99 * r);
	int gByte = int(255.99 * g);
	int bByte = int(255.99 * b);

	// We are going to write to the ppm file with this
	out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}


#endif 
