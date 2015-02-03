/*
 *  shader/refract.h
 *  RRT
 *
 *  Created by Ray Bellis on 23/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __SHADER_REFRACT_H
#define __SHADER_REFRACT_H

#include <rrt/shader.h>

namespace Shader {

	class refract : public base {

	protected:
		colour						m_colour;
		float						m_ior;
		float						m_smooth;

	public:
		refract(const scene& scene, const colour& c, float ior, float smooth) :
			base(scene), m_colour(c), m_ior(ior), m_smooth(smooth) {}

		virtual colour shade(const ray& r, const point3& p, const vector3& n, const uvcoord&) const {
			colour c;

			if (m_colour.is_black()) {
				return c;
			}

			bool total;
			vector3 d = vector3::refract(r.direction(), n, r.ior(), m_ior, total);
			if (total) {
				return c;
			}

			d.perturb(m_smooth);
			c = trace(ray(r, p, d, m_ior));
			c *= m_colour;

			return c;
		};
	};

} // namespace Shader

#endif // __SHADER_REFRACT_H
