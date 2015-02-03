/*
 *  matrix4.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 27/05/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#include "matrix4.h"

static double identity[] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

static void __copy(double *dst, const double *src)
{
	for (int i = 0; i < 16; ++i) {
		dst[i] = src[i];
	}
}

matrix4::matrix4()
{
	__copy(d, identity);
}

matrix4::matrix4(const matrix4& rhs)
{
	__copy(d, rhs.d);
}

matrix4::matrix4(const array& a)
{
	__copy(d, a);
}

matrix4& matrix4::operator=(const matrix4& rhs)
{
	__copy(d, rhs.d);
	return *this;
}

matrix4 matrix4::operator*(const matrix4& rhs) const
{
	array a;
	const array& b = rhs.d;

	a[ 0] = d[ 0] * b[ 0] + d[ 1] * b[ 4] + d[ 2] * b[ 8] + d[ 3] * b[12];
	a[ 1] = d[ 0] * b[ 1] + d[ 1] * b[ 5] + d[ 2] * b[ 9] + d[ 3] * b[13];
	a[ 2] = d[ 0] * b[ 2] + d[ 1] * b[ 6] + d[ 2] * b[10] + d[ 3] * b[14];
	a[ 3] = d[ 0] * b[ 3] + d[ 1] * b[ 7] + d[ 2] * b[11] + d[ 3] * b[15];

	a[ 4] = d[ 4] * b[ 0] + d[ 5] * b[ 4] + d[ 6] * b[ 8] + d[ 7] * b[12];
	a[ 5] = d[ 4] * b[ 1] + d[ 5] * b[ 5] + d[ 6] * b[ 9] + d[ 7] * b[13];
	a[ 6] = d[ 4] * b[ 2] + d[ 5] * b[ 6] + d[ 6] * b[10] + d[ 7] * b[14];
	a[ 7] = d[ 4] * b[ 3] + d[ 5] * b[ 7] + d[ 6] * b[11] + d[ 7] * b[15];

	a[ 8] = d[ 8] * b[ 0] + d[ 9] * b[ 4] + d[10] * b[ 8] + d[11] * b[12];
	a[ 9] = d[ 8] * b[ 1] + d[ 9] * b[ 5] + d[10] * b[ 9] + d[11] * b[13];
	a[10] = d[ 8] * b[ 2] + d[ 9] * b[ 6] + d[10] * b[10] + d[11] * b[14];
	a[11] = d[ 8] * b[ 3] + d[ 9] * b[ 7] + d[10] * b[11] + d[11] * b[15];

	a[12] = d[12] * b[ 0] + d[13] * b[ 4] + d[14] * b[ 8] + d[15] * b[12];
	a[13] = d[12] * b[ 1] + d[13] * b[ 5] + d[14] * b[ 9] + d[15] * b[13];
	a[14] = d[12] * b[ 2] + d[13] * b[ 6] + d[14] * b[10] + d[15] * b[14];
	a[15] = d[12] * b[ 3] + d[13] * b[ 7] + d[14] * b[11] + d[15] * b[15];

	return matrix4(a);
}

matrix4 matrix4::operator~() const
{
	array a;
	int k = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j, ++k) {
			a[k] = d[j * 4 + i];			// swapped row/col
		}
	}

	return matrix4(a);
}

double& matrix4::operator[](const int n)
{
	return d[n];
}

double matrix4::operator[](const int n) const
{
	return d[n];
}

vector3 matrix4::operator*(const vector3& v) const
{
	double x = d[0] * v.x + d[1] * v.y + d[ 2] * v.z;
	double y = d[4] * v.x + d[5] * v.y + d[ 6] * v.z;
	double z = d[8] * v.x + d[9] * v.y + d[10] * v.z;

	return vector3(x, y, z);
}

point3 matrix4::operator*(const point3& p) const
{
	double x = d[ 0] * p.x + d[ 1] * p.y + d[ 2] * p.z + d[ 3];
	double y = d[ 4] * p.x + d[ 5] * p.y + d[ 6] * p.z + d[ 7];
	double z = d[ 8] * p.x + d[ 9] * p.y + d[10] * p.z + d[11];
	double w = d[12] * p.x + d[13] * p.y + d[14] * p.z + d[15];
	double wr = 1.0 / w;

	return point3(x * wr, y * wr, z * wr);
}
