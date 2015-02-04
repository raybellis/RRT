/*
 *  core/hit.h
 *  RRT
 *
 *  Created by Ray Bellis on 29/08/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_HIT_H
#define __CORE_HIT_H

#include <vector>
#include "geom.h"
#include "transform.h"

class primitive;

class hit {

protected:
	point3::num				m_distance;
	const primitive*		m_primitive;
	const transform*		m_transform;

public:
	hit(point3::num distance, const primitive* primitive);
	hit(const hit& rhs);

public:
	hit&					operator=(const hit& rhs);
	point3::num				distance() const	{ return m_distance; }
	const primitive&		what() const		{ return *m_primitive; }
	const transform&		transform() const	{ return *m_transform; }

	bool					operator<(const hit& rhs) const;
};

typedef std::vector<hit>	hits;

#endif // __CORE_HIT_H
