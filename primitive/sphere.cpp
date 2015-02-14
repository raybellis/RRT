/*
 *  primitive/sphere.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <cmath>
#include <rrt/math.h>
#include "sphere.h"

sphere::sphere()
{
}

int sphere::intersect(const ray& ray, hits& hits) const
{
	int nroots = 0;

	vector3 o = ray.origin();
	vector3 d = ray.direction();

	double a = d.dot(d);
	double b = 2 * d.dot(o);
	double c = o.dot(o) - 1;
	double disc = b * b - 4 * a * c;
	if (disc <= 0.0) return 0;

	disc = sqrt(disc);
	double q = -0.5 * ((b < 0) ? (b - disc) : (b + disc));

	double t0 = q / a;
	double t1 = c / q;

	if (t0 > math::epsilon) {
		hits.emplace_back(hit(t0, this));
		++nroots;
	}

	if (t1 > math::epsilon) {
		hits.emplace_back(hit(t1, this));
		++nroots;
	}

	return nroots;
}

vector3 sphere::normal(const point3& p, const hitinfo *) const
{
	return vector3(p).normalise();
}

uvcoord sphere::uvmap(const point3& p) const
{
	vector3 n = vector3(p);
	double u = 0.5 - atan2(n.z, n.x) * math::one_over_2pi;
	double v = 0.5 - asin(n.y) * math::one_over_pi;
	return uvcoord(u, v, 0);
}
