/*
 *  core/shader.h
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_SHADER_H
#define __CORE_SHADER_H

#include "rrt.h"

//---------------------------------------------------------
// forward declarations
class scene;
class ray;
class point3;
class vector3;

//---------------------------------------------------------

namespace Shader {

	class base {

	protected:
		const scene&			m_scene;

	public:
		base(const scene& scene);

	public:
		virtual colour shade(const ray& ray, const point3& p, const vector3& n, const uvcoord& uv) const = 0;
		colour trace(const ray& ray) const;
	};

	class constant : public base {

	protected:
		colour					m_colour;

	public:
		constant(const scene& scene, colour c) : base(scene), m_colour(c) {}

		virtual colour shade(const ray&, const point3&, const vector3&, const uvcoord&) const {
			return m_colour;
		};

	};

}; // namespace

typedef Shader::base shader;

//---------------------------------------------------------

#endif // __CORE_SHADER_H
