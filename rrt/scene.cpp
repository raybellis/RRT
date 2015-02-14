/*
 *  scene.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <algorithm>

#include "scene.h"
#include "math.h"

scene::scene() : m_background(0.5)
{
}

colour scene::trace(const ray& ray) const
{
	hits hits;
	hits.reserve(20);

	if ((ray.level() < 6) && intersect(ray, hits) > 0) {

		const auto& hit = *std::min_element(hits.begin(), hits.end());
		const auto prim = hit.what();
		const auto trans = hit.transform();
		const auto hi = hit.hitinfo();

		const point3 pw = ray.point_at(hit.distance());
		const point3 po = trans->world2object(pw);

		const vector3 no = prim->normal(po, hi);
		vector3 nw = trans->normal2world(no);
		nw.normalise();

		// treat primitives as two sided
		if (nw.dot(ray.direction()) > 0) {
			nw.flip();
		}

		return prim->shade(ray, pw, nw);
	}

	return m_background;
}
