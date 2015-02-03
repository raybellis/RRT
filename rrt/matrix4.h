/*
 *  core/matrix4.h
 *  RRT
 *
 *  Created by Ray Bellis on 11/06/2013.
 *  Copyright 2013 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_MATRIX4_H
#define __CORE_MATRIX4_H

#include "geom.h"

class matrix4 {

public:
	typedef double			array[16];

protected:
	array					d;

public:
	matrix4();
	matrix4(const matrix4& rhs);
	matrix4(const array& a);

	matrix4&				operator=(const matrix4& rhs);

public:
	matrix4					operator*(const matrix4& rhs) const;
	matrix4					operator~() const;

	double&					operator[](const int n);
	double					operator[](const int n) const;

	vector3					operator*(const vector3& v) const;
	point3					operator*(const point3& p) const;
};

#endif // __CORE_MATRIX4_H
