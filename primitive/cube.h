/*
 *  primitive/cube.h
 *  RRT
 *
 *  Created by Ray Bellis on 24/08/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#ifndef __PRIMITIVE_CUBE_H
#define __PRIMITIVE_CUBE_H

#include <rrt/primitive.h>

class cube : public primitive {

public:
	cube();

public:
	virtual int				intersect(const ray& ray, hits& hits) const;
	virtual vector3			normal(const point3& p) const;
	virtual uvcoord			uvmap(const point3& point) const;

};

#endif // __PRIMITIVE_CUBE_H
