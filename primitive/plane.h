/*
 *  primitive/plane.h
 *  RRT
 *
 *  Created by Ray Bellis on 21/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __PRIMITIVE_PLANE_H
#define __PRIMITIVE_PLANE_H

#include <rrt/primitive.h>

class plane : public primitive {

public:
	plane();

public:
	int						intersect(const ray& ray, hits& hits) const;
	vector3					normal(const point3& p, const hitinfo *) const;
	uvcoord					uvmap(const point3& p) const;
};

#endif // __PRIMITIVE_PLANE_H
