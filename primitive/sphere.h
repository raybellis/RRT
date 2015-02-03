/*
 *  primitive/sphere.h
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __PRIMITIVE_SPHERE_H
#define __PRIMITIVE_SPHERE_H

#include <rrt/primitive.h>

class sphere : public primitive {

public:
	sphere();

public:
	virtual int				intersect(const ray& ray, hits& hits) const;
	virtual vector3			normal(const point3& p) const;
	virtual uvcoord			uvmap(const point3& point) const;

};

#endif // __PRIMITIVE_SPHERE_H
