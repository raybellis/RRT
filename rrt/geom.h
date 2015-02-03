/*
 *  core/geom.h
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_GEOM_H
#define __CORE_GEOM_H

#include <math.h>
#include <cmath>
#include "tuple3.h"

class point3 : public tuple3<double> {

public:
	point3();
	point3(const num x, const num y, const num z);
	point3(const point3& rhs);
};

class vector3 : public tuple3<double> {

public:
	vector3();
	vector3(const num x, const num y, const num z);
	vector3(const array& a);
	vector3(const vector3& rhs);
	vector3(const point3& a, const point3& b);
	vector3(const point3& p);

public:
	num						dot(const vector3& rhs) const;
	num						length() const;
	vector3&				normalise();
	vector3&				flip();
	vector3&				perturb(num s);
	vector3&				phong(num exponent);
	
public:
	static vector3			cross(const vector3& lhs, const vector3& rhs);
	static num				dot(const vector3& lhs, const vector3& rhs);

	static vector3			reflect(const vector3& i, const vector3& n);
	static vector3			refract(const vector3& i, const vector3& n,
									float ior1, float ior2, bool& total);
	static vector3			random();
};

inline vector3::num vector3::dot(const vector3& rhs) const
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

inline vector3::num vector3::length() const
{
	return sqrt(dot(*this));
}

inline vector3::num vector3::dot(const vector3& lhs, const vector3& rhs)
{
	return lhs.dot(rhs);
}

inline vector3 vector3::cross(const vector3& lhs, const vector3& rhs)
{
	num x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
	num y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
	num z = (lhs.x * rhs.y) - (lhs.y * rhs.x);
	return vector3(x, y, z);
}

#endif // __CORE_GEOM_H
