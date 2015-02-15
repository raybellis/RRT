/*
 *  primitive/triangle.h
 *  RRT
 *
 *  Created by Ray Bellis on 14/02/2015.
 *  Copyright 2015 Ray Bellis. All rights reserved.
 *
 */

#ifndef __PRIMITIVE_TRIANGLE_H
#define __PRIMITIVE_TRIANGLE_H

#include <rrt/primitive.h>

class triangle : public primitive {

protected:
	const point3			p0;
	const vector3			e1;
	const vector3			e2;

	const vector3			n0;
	const vector3			n1;
	const vector3			n2;

	bool					smooth;

public:
	triangle(const point3& p0, const point3& p1, const point3& p2);

	triangle(const point3& p0, const point3& p1, const point3& p2,
			 const vector3& n0, const vector3& n1, const vector3& n2);

public:
	virtual int				intersect(const ray& ray, hits& hits) const;
	virtual vector3			normal(const point3& p, const hitinfo *hi) const;
	virtual uvcoord			uvmap(const point3& point) const;

};

#endif // __PRIMITIVE_TRIANGLE_H
