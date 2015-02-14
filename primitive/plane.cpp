/*
 *  primitive/plane.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 21/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <cmath>
#include <rrt/math.h>
#include "plane.h"

static vector3 s_normal(0, 1, 0);

plane::plane()
{
}

int plane::intersect(const ray& ray, hits& hits) const
{
	double vd = s_normal.dot(ray.direction());

	// reject parallel rays
	if (fabs(vd) < math::epsilon) return 0;

	// back-face culling
	if (vd > 0) return 0;

	vector3 pn(point3(0, 0, 0), ray.origin());
	double v0 = -pn.dot(s_normal);
	double t = v0  /vd;
	if (t < 0) {
		return 0;
	}

	hits.emplace_back(hit(t, this));
	return 1;
}

vector3 plane::normal(const point3&, const hitinfo *) const
{
	return s_normal;
}

uvcoord plane::uvmap(const point3& p) const
{
	point3 t(p);
	point3::num dx = t.x - ::floor(t.x);
	point3::num dy = t.y - ::floor(t.y);
	point3::num dz = t.z - ::floor(t.z);
	return uvcoord(dx, dy, dz);
}
