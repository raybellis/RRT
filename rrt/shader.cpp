/*
 *  shader.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include "shader.h"
#include "ray.h"
#include "surface.h"
#include "scene.h"

namespace Shader {
	
base::base(const scene& scene) : m_scene(scene)
{
}

colour base::trace(const ray& ray) const
{
	return m_scene.trace(ray);
}

}; // namespace
