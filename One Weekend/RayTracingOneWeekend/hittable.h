#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>

#include "ray.h"
#include "interval.h"
#include "material.h"


//-----------------------------------------------------------------------------
//                          Ray Tracing Tutorial - Hit Record
//
//	A ray can hit multiple objects in a scene. We need a way to store where the 
//	ray hit someting in the scene.  
//-----------------------------------------------------------------------------

class material;

class hit_record {
public:
	vec3 p;
	vec3 normal;
	std::shared_ptr<material> mat;
	double t;
	bool front_face;		// Is the normal at the hit point facing against the ray or not

	void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};


//-----------------------------------------------------------------------------
//                          Ray Tracing Tutorial - Hittable
//
//	This is an abstract class, we are going to derived every class wich we can
//	see by the renderer like spheres or triangels, planes etc and these class 
//	have to implements these funtions. 
//-----------------------------------------------------------------------------

class hittable {
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
}; 

#endif