#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"

#include <vector>

//-----------------------------------------------------------------------------
//                       Ray Tracing Tutorial - Hittable List
//
//	This class is simply the scene which is going to be rendered. In this 
//	class. We store a list of references. These referencses must be derived 
//	from the hittable class. 
//-----------------------------------------------------------------------------

class hittable_list : public hittable {
public:
	std::vector<std::shared_ptr<hittable>> objects;							// List of hittable objects

	// Constructors
	hittable_list() {};
	hittable_list(std::shared_ptr<hittable> object) { add(object); }

	// Deconstructors
	void clear() { objects.clear(); }

	// Add new hittable reference to the scene 
	void add(std::shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	// With this fuction we will itarate every hittable objext in the scene. 
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		hit_record temp_rec;
		bool hit_by_anything = false;
		auto closest_so_far = ray_t.max;

		for (const auto& object : objects) {
			if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
				hit_by_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_by_anything;
	}
};

#endif