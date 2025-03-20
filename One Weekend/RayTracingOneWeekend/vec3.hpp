#ifndef VEC3_HPP
#define VEC3_HPP


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

// We use point and vec3. It's an alias
using point = vec3;

/* VECTOR UTILITY FUNCTIONS */

// This project using streams to create image data. Thats the reson we need overload the << operator
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline vec3 operator/(const vec3& v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

#endif