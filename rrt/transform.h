/*
 *  core/transform.h
 *  RRT
 *
 *  Created by Ray Bellis on 27/05/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_TRANSFORM_H
#define __CORE_TRANSFORM_H

#include "geom.h"
#include "matrix4.h"
#include "ray.h"

/*
 * 'mat' is the 4x4 homogenous matrix converting from object coordinates
         to world coordinates
 *
 * 'inv' is its inverse, i.e. from world coordinates to object coordinates
 */

class transform {

private:
	matrix4					mat, inv;

private:
	transform(matrix4 mat, matrix4 inv);

public:
	transform();
	transform(const transform& t);
	transform(transform&& t);

public:
	transform&				operator=(const transform& t);
	transform				operator*(const transform& t) const;

public:
	ray						world2object(const ray& r) const;
	point3					world2object(const point3& p) const;
	vector3					normal2world(const vector3& v) const;

public:
	static transform		translate(double x, double y, double z);
	static transform		translate(const vector3& v);
	static transform		scale(double x, double y, double z);
	static transform		scale(double s);
	static transform		rotate(double x, double y, double z, double theta);
	static transform		rotate(const vector3& v, double theta);
	static transform		rotate_x(double theta);
	static transform		rotate_y(double theta);
	static transform		rotate_z(double theta);
};

inline transform transform::translate(const vector3& v)
{
	return transform::translate(v.x, v.y, v.z);
}

inline transform transform::scale(double s)
{
	return transform::scale(s, s, s);
}

inline transform transform::rotate(const vector3& u, double theta)
{
	return transform::rotate(u.x, u.y, u.z, theta);
}   

inline transform transform::rotate_x(double theta)
{
	return transform::rotate(1, 0, 0, theta);
}

inline transform transform::rotate_y(double theta)
{
	return transform::rotate(0, 1, 0, theta);
}

inline transform transform::rotate_z(double theta)
{
	return transform::rotate(0, 0, 1, theta);
}

#endif // __CORE_TRANSFORM_H
