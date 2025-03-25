#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

class hit_record {
public:
	vec3 p;
	vec3 normal;
	double t;
	bool front_face;

	void set_face_normal(const ray& r, const vec3& outward_nomrmal) {
		front_face = dot(r.direction(), outward_nomrmal) < 0;
		normal = front_face ? outward_nomrmal : -outward_nomrmal;
	}
};

class hittable {
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
}; 

#endif