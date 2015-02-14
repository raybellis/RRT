/*
 *  primitive/cube.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 24/08/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#include <cmath>
#include <limits>

#include <rrt/math.h>
#include "cube.h"

cube::cube()
{
}

int cube::intersect(const ray& ray, hits& hits) const
{
	point3::num tnear = std::numeric_limits<point3::num>::min();
	point3::num tfar  = std::numeric_limits<point3::num>::max();

	point3::array ov, dv;
	ray.origin().get(ov);
	ray.direction().get(dv);

	for (int i = 0; i < 3; ++i) {
		point3::num d = dv[i];
		if (fabs(d) < math::epsilon) {
			if (fabs(ov[i]) > 1) return 0;
		} else {
			d = 1.0 / d;
			point3::num t0 = (-1 - ov[i]) * d;
			point3::num t1 = (+1 - ov[i]) * d;
			
			if (t0 > t1) {
				std::swap(t0, t1);
			}
			
			if (t0 > tnear) {
				tnear = t0;
			}
			
			if (t1 < tfar) {
				tfar = t1;
			}
			
			if (tnear > tfar) {
				return 0;
			}
			
			if (tfar < math::epsilon) {
				return 0;
			}
		}
	}
	
	if (tnear < math::epsilon) {
		return 0;
	}
	
	hits.emplace_back(hit(tnear, this));
	hits.emplace_back(hit(tfar, this));
	
	return 2;
}

vector3	cube::normal(const point3& pt, const hitinfo*) const
{
	point3::array p;
	vector3::array n;
	
	pt.get(p);
	for (int i = 0; i < 3; ++i) {
		n[0] = n[1] = n[2] = 0;
		if (fabs(p[i] + 1) < math::epsilon) {
			n[i] = -1;
			break;
		} else if (fabs(p[i] - 1) < math::epsilon) {
			n[i] = +1;
			break;
		}
	}
	return vector3(n);
}

uvcoord cube::uvmap(const point3&) const
{
	return uvcoord(0, 0, 0);
}
