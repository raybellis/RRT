/*
 *  core/ray.h
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_RAY_H
#define __CORE_RAY_H

#include <set>
#include "geom.h"

class ray {

private:
	ray()					{}				// private ctor
	
public:
	typedef unsigned int	level_t;
	
protected:
	point3					m_origin;
	vector3					m_direction;
	level_t					m_level;
	float					m_ior;
	
public:
	ray(const point3& origin, const vector3& direction, level_t level = 0, float ior = 1.0);
	ray(const ray& old, const point3& origin, const vector3& direction, float ior);
	ray(const ray& old, const point3& origin, const vector3& direction);

public:
	point3					point_at(point3::num d) const;
	const point3&			origin() const		{ return m_origin; }
	const vector3&			direction() const	{ return m_direction; }
	level_t					level() const		{ return m_level; }
	float					ior() const			{ return m_ior; }

};

#endif // __CORE_RAY_H
