/*
 *  primitive/triangle.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 14/02/2015.
 *  Copyright 2015 Ray Bellis. All rights reserved.
 *
 */

#include <rrt/math.h>
#include "triangle.h"

struct hitinfo_triangle : virtual public hitinfo {
    double	u, v;
    hitinfo_triangle(double u, double v) : u(u), v(v) {}
    virtual ~hitinfo_triangle() {};
};

triangle::triangle(const point3& p0, const point3& p1, const point3& p2)
: p0(p0), e1(p0, p1), e2(p0, p2), n0(vector3::cross(e1, e2)), n1(n0), n2(n0), smooth(false)
{
}

triangle::triangle(const point3& p0, const point3& p1, const point3& p2,
				   const vector3& n0, const vector3& n1, const vector3& n2)
: p0(p0), e1(p0, p1), e2(p0, p2), n0(n0), n1(n1), n2(n2), smooth(true)
{
}

int triangle::intersect(const ray& ray, hits& hits) const
{
	// NB: triangles are assumed to be in world space (or at
	//     least relative to their parent)
	vector3 pvec = vector3::cross(ray.direction(), e2);
	double det = e1.dot(pvec);
	if (::fabs(det) < math::epsilon) return 0;

	double invDet = 1.0 / det;
	vector3 tvec(p0, ray.origin());

	double u = tvec.dot(pvec) * invDet;
	if (u < 0 || u > 1) return 0;

	vector3 qvec = vector3::cross(tvec, e1);
	double v = ray.direction().dot(qvec) * invDet;
	if (v < 0 || u + v > 1) return 0;

	double t = e2.dot(qvec) * invDet;
	if (t > math::epsilon) {		// avoid self intersection
		auto hi = new hitinfo_triangle(u, v);
		assert(hi != nullptr);
		hits.emplace_back(hit(t, this, hi));
		return 1;
	}

	return 0;
}

vector3	triangle::normal(const point3&, const hitinfo *hi) const
{
	if (!smooth) {
		return n0;
	}

	auto *info = dynamic_cast<const hitinfo_triangle*>(hi);
	double u = info->u;
	double v = info->v;
	double w = 1 - u - v;
	vector3 n;
	n.add_scaled(n0, w);
	n.add_scaled(n1, u);
	n.add_scaled(n2, v);
	return n;
}

uvcoord triangle::uvmap(const point3&) const
{
	return uvcoord(0, 0, 0);
}
