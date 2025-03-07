#ifndef VEC3_HPP
#define VEC3_HPP
#include <cmath>
#include <iostream>

class vec3 {
public:
	double e[3];

	// Constructors
	vec3() : e{ 0, 0, 0 } {}
	vec3(double e1, double e2, double e3) : e{ e1, e2, e3 } {}

	// Getteres
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }


	// Operator overloading 
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](const int i) const { return e[i]; }
	double& operator[](const int i) { return e[i]; }

	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t) {
		return *this *= 1/t;
	}

	double length() const {
		return std::sqrt(length_squerd());
	}

	double length_squerd() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

};

#endif