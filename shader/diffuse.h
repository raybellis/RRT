/*
 *  shader/diffuse.h
 *  RRT
 *
 *  Created by Ray Bellis on 22/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __SHADER_DIFFUSE_H
#define __SHADER_DIFFUSE_H

#include <rrt/shader.h>

namespace Shader {

	class diffuse : public base {

	protected:
		const colour&				m_colour;

	public:
		diffuse(const scene& scene, const colour& c) : base(scene), m_colour(c) {} 

		virtual colour shade(const ray& ray_in, const point3& p, const vector3& n, const uvcoord&) const {
			colour c;
			if (m_colour.is_black()) {
				return c;
			}

			vector3 d = vector3::random();
			double dp = n.dot(d);
			if (dp < 0) {
				dp = -dp;
				d.flip();
			}

			ray ray_out(ray_in, p, d);
			c = trace(ray_out);
			c *= m_colour;
			c *= dp;

			return c;
		};

	};

};

#endif // __SHADER_DIFFUSE_H
