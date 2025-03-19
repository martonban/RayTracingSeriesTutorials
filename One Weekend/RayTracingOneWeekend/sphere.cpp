#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {
public:
	sphere(const vec3& center, double radius) : _center(center), _radius(std::fmax(0, radius)) {}

	bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
		vec3 oc = _center - r.origin();
		auto a = r.direction().length_squerd();
		auto h = dot(r.direction(), oc);
		auto c = oc.length_squerd() - _radius * _radius;

		auto discriminant = h * h - a * c;
		if (discriminant < 0)
			return false;

		auto sqrtd = std::sqrt(discriminant);

		// find the nearest toot thet lies in the acceptable range.
		auto root = (h - sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root) {
			root = (h + sqrtd) / a;
			if (root <= ray_tmin || ray_tmax <= root) {
				return false;
			}
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		rec.normal = (rec.p - _center) / _radius;

		return true;
	}

private:
	vec3 _center;
	double _radius;

};

#endif // !SPHERE_HPP
