/*
 *  ray.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include "ray.h"

ray::ray(const point3& origin, const vector3& direction,
		 level_t level, float ior) :
	m_origin(origin), m_direction(direction), m_level(level), m_ior(ior)
{
}

ray::ray(const ray& old, const point3& origin, const vector3& direction, float ior) :
	m_origin(origin), m_direction(direction),
	m_level(old.m_level + 1), m_ior(ior)
{
}

ray::ray(const ray& old, const point3& origin, const vector3& direction) :
	m_origin(origin), m_direction(direction),
	m_level(old.m_level + 1), m_ior(old.m_ior)
{
}

point3 ray::point_at(point3::num d) const
{
	point3 tmp(m_origin);
	tmp.add_scaled(m_direction, d);
	return tmp;
}
