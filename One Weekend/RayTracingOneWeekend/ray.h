#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
	// Constreuctors
	ray() {}
	ray(const vec3& origin, const vec3& dir) : _origin(_origin), _dir(dir) {}


	// Getters
	const vec3& origin() const { return _origin; }
	const vec3& direction() const { return _dir; }

	// P(t) = A + tb
	vec3 at(double t) const {
		return _origin + t * _dir;
	}

private:
	vec3 _origin;
	vec3 _dir;
};


#endif