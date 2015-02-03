/*
 *  transform.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 27/05/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#include "transform.h"

transform::transform() : mat(), inv()
{
}

transform::transform(matrix4 _mat, matrix4 _inv) :
	mat(_mat), inv(_inv)
{
}

transform::transform(const transform& t)
{
	mat = t.mat;
	inv = t.inv;
}

transform::transform(transform&& t) : mat(std::move(t.mat)), inv(std::move(t.inv))
{
}

transform& transform::operator=(const transform& t)
{
	mat = t.mat;
	inv = t.inv;
	return *this;
}

ray transform::world2object(const ray& r) const
{
	return ray(inv * r.origin(), inv * r.direction(), r.level(), r.ior());
}

point3 transform::world2object(const point3& p) const
{
	return inv * p;
}

/*
 * normal transformation requires multiplication by the
 * transpose of the inverse of the object to world matrix,
 */
vector3 transform::normal2world(const vector3& v) const
{
	return ~inv * v;
}

transform transform::operator*(const transform& t) const
{
	return transform(mat * t.mat, t.inv * inv);
}

transform transform::translate(double x, double y, double z)
{
	matrix4::array mat = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};

	matrix4::array inv = {
		1, 0, 0, -x,
		0, 1, 0, -y,
		0, 0, 1, -z,
		0, 0, 0,  1
	};

	return transform(mat, inv);
}

transform transform::scale(double x, double y, double z)
{
	matrix4::array mat = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};

	x = 1.0 / x;
	y = 1.0 / y;
	z = 1.0 / z;

	matrix4::array inv = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};

	return transform(mat, inv);
}

transform transform::rotate(double x, double y, double z, double theta)
{
	double c = cos(theta);
	double s = sin(theta);

	matrix4::array terms = {
		c + x * x * (1 - c), x * y * (1 - c) - z * s, x * z * (1 - c) + y * s, 0,
		y * x * (1 - c) + z * s, c + y * y * (1 - c), y * z * (1 - c) - x * s, 0,
		z * x * (1 - c) - y * s, z * y * (1 - c) + x * s, c + z * z * (1 - c), 0,
		0, 0, 0, 1
	};

	matrix4 mat(terms);
	matrix4 inv = ~mat;

	return transform(mat, inv);
}
