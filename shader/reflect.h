/*
 *  shader/reflect.h
 *  RRT
 *
 *  Created by Ray Bellis on 21/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __SHADER_REFLECT_H
#define __SHADER_REFLECT_H

#include <rrt/shader.h>

namespace Shader {
	
	class reflect : public base {

	protected:
		colour			m_colour;
		float			m_smooth;

	public:
		reflect(const scene& scene, colour c, float smooth) : base(scene), m_colour(c), m_smooth(smooth) {}

		virtual colour shade(const ray& r, const point3& p, const vector3& n, const uvcoord&) const {
			colour c;
		
			if (m_colour.is_black()) {
				return c;
			}
		
			vector3 d = vector3::reflect(r.direction(), n);
			d.perturb(m_smooth);
		
			c = trace(ray(r, p, d));
			c *= m_colour;
			return c;
		};
	};

} // namespace Shader

#endif // __SHADER_REFLECT_H
