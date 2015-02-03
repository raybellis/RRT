/*
 *  core/rrt.h
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_RRT_H
#define __CORE_RRT_H

#include "math.h"
#include "tuple3.h"

class colour : public tuple3<float> {

public:
	num&					r() { return x; };
	num&					g() { return y; };
	num&					b() { return z; };

public:
	colour();
	colour(const num r, const num g, const num b);
	colour(const num grey);

public:
	colour&					clamp();
	bool					is_black() const;

	colour&					operator*=(const colour& rhs);

};

class uvcoord : public tuple3<float> {

public:
	num&					u() { return x; };
	num&					v() { return y; };
	num&					w() { return z; };

public:
	uvcoord(const tuple3<float>& uvw) :
		tuple3<float>(uvw) {}

	uvcoord(const num u, const num v, const num w) :
		tuple3<float>(u, v, w) {}

};

inline colour::colour() :
	tuple3<num>(0, 0, 0)
{
}

inline colour::colour(const num r, const num g, const num b) :
	tuple3<num>(r, g, b)
{
}

inline colour::colour(const num grey) :
	tuple3<num>(grey, grey, grey)
{
}

inline colour& colour::clamp()
{
	x = math::clamp(x);
	y = math::clamp(y);
	z = math::clamp(z);
	return *this;
}

inline colour& colour::operator*=(const colour& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

inline bool colour::is_black() const
{
	num limit = 1e-4;
	return (x < limit) && (y < limit) && (z < limit);
}

#endif // __CORE_RRT_H
