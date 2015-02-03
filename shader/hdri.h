/*
 *  shader/hdri.h
 *  RRT
 *
 *  Created by Ray Bellis on 21/05/2013.
 *  Copyright 2013 Ray Bellis. All rights reserved.
 *
 */

#ifndef __SHADER_HDRI_H
#define __SHADER_HDRI_H

#include <rrt/shader.h>
#include <rrt/image.h>

namespace Shader {

	class hdri : public base {

	protected:
		const image*			m_img;
		float					m_gain;

	public:
		hdri(const scene& scene, const image& img, float gain = 1.0f) : base(scene), m_img(&img), m_gain(gain) { }

		hdri(const scene& scene, const image* img, float gain = 1.0f) : base(scene), m_img(img), m_gain(gain) { }

		virtual colour shade(const ray&, const point3&, const vector3&, const uvcoord& uv) const {
			colour c = m_img->get_colour(uv);
			c *= m_gain;
			return c;
		};
	};

} // namespace Shader

#endif // __SHADER_HDRI_H
