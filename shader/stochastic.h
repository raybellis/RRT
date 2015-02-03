/*
 *  shader/stochastic.h
 *  RRT
 *
 *  Created by Ray Bellis on 22/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __SHADER_STOCHASTIC_H
#define __SHADER_STOCHASTIC_H

#include <rrt/surface.h>
#include <rrt/shader.h>
#include "diffuse.h"
#include "reflect.h"
#include "refract.h"

namespace Shader {

	class stochastic : public base {
		
	protected:
		const surface&			m_surface;
		Shader::diffuse			m_diffuse;
		Shader::reflect			m_reflect;
		Shader::refract			m_refract;

	public:
		stochastic(const scene& scene, const surface& s)
			: base(scene),
			  m_surface(s),
			  m_diffuse(scene, s.diffuse()),
			  m_reflect(scene, s.reflect(), s.smooth()),
			  m_refract(scene, s.transmit(), s.ior(), s.smooth()) {}
		
		virtual colour shade(const ray& ray, const point3& p, const vector3& n, const uvcoord& uv) const {
			colour c;
			c += m_diffuse.shade(ray, p, n, uv);
			c += m_reflect.shade(ray, p, n, uv);
			c += m_refract.shade(ray, p, n, uv);
			c += m_surface.ambient();
			return c;
		};

	};

} // namespace Shader

#endif // __SHADER_STOCHASTIC_H
