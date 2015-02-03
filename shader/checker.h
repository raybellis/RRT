/*
 *  shader/checker.h
 *  RRT
 *
 *  Created by Ray Bellis on 24/08/2014.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __SHADER_CHECKER_H
#define __SHADER_CHECKER_H

#include <rrt/shader.h>

namespace Shader {

	class checker : public base {

	protected:
		const shader*				m_s1;
		const shader*				m_s2;
		float						m_size;

	public:
		checker(const scene& scene, const shader *s1, const shader *s2, float size = 0.25) 
			: base(scene), m_s1(s1), m_s2(s2), m_size(size) {}

		virtual colour shade(const ray& ray, const point3& p, const vector3& n, const uvcoord& uv) const {
			bool x = uv.x < m_size || uv.x >= (1 - m_size);
			bool y = uv.y < m_size || uv.y >= (1 - m_size);
			bool z = uv.z < m_size || uv.z >= (1 - m_size);
			bool which = x ^ y ^ z;

			return which ? m_s1->shade(ray, p, n, uv) : m_s2->shade(ray, p, n, uv);
		}
	};

} // namespace Shader

#endif // __SHADER_CHECKER_H
