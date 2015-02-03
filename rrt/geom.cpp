/*
 *  geom.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <cmath>
#include "math.h"
#include "geom.h"

//----------------------------------------------------------

point3::point3()
{
}

point3::point3(const num _x, const num _y, const num _z) :
	tuple3<num>(_x, _y, _z)
{
}

point3::point3(const point3& rhs) :
	tuple3<num>(rhs)
{
}

//----------------------------------------------------------

vector3::vector3() :
	tuple3<num>()
{
}

vector3::vector3(const num _x, const num _y, const num _z) :
	tuple3<num>(_x, _y, _z)
{
}

vector3::vector3(const vector3& rhs) :
	tuple3<num>(rhs)
{
}

vector3::vector3(const point3& a, const point3& b) :
	tuple3<num>(b.x - a.x, b.y - a.y, b.z - a.z)
{
}

vector3::vector3(const point3& p) :
	tuple3<num>(p.x, p.y, p.z)
{
}

vector3::vector3(const array& a) :
	tuple3<num>(a)
{
}

vector3& vector3::normalise()
{
	num scale = 1.0 / length();
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

vector3& vector3::flip()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

vector3 vector3::random()
{
	num ran1, ran2, ransq;
	
	do {
		ran1 = 1.0 - 2.0 * math::random();
		ran2 = 1.0 - 2.0 * math::random();
		ransq = (ran1 * ran1) + (ran2 * ran2);
	} while (ransq > 1.0);
	
	double ranh = 2.0 * sqrt(1.0 - ransq);
	
	num x = ran1 * ranh;
	num y = ran2 * ranh;
	num z = 1.0 - 2.0 * ransq;
	
	return vector3(x, y, z);
}

vector3 vector3::reflect(const vector3& i, const vector3& n)
{
	vector3 d(i);
	d.add_scaled(n, -2.0 * i.dot(n));
	return d;
}

vector3 vector3::refract(const vector3& i, const vector3& n, float ior1, float ior2, bool& total)
{
	vector3 d;
	vector3 nr(n);
	double c1 = i.dot(n);
	if (c1 <= 0) {
		c1 = -c1;
		nr.flip();
	}

	double eta = ior1 / ior2;
	double t = 1.0 + (eta * eta) * (c1 * c1 - 1.0);
	
	total = (t < 0); // total internal reflection
	if (!total) {
		t = eta * c1 - sqrt(t);
		d.add_scaled(i, eta);
		d.add_scaled(nr, -t);
	}
	return d;
}

vector3& vector3::perturb(num s)
{
	if (s > math::epsilon) {
		add_scaled(vector3::random(), s);
	}
	return *this;
}

vector3& vector3::phong(const num exponent)
{
	// find orthogonal vector basis
	vector3 W(*this);
	vector3 U = vector3::cross(W, vector3(1, 0, 0));
	if (U.dot(U) < math::epsilon) {
		U = vector3::cross(W, vector3(0, 1, 0));
	}
	vector3 V = vector3::cross(W, U);
	
	// pick new random vector in UVW space
	num zeta1 = math::random();
	num zeta2 = math::random();
	num phi = 2 * math::pi * zeta1;
	num sin_phi = sin(phi);
	num cos_phi = cos(phi);
	num cos_theta = pow(zeta2, 1.0 / (exponent + 1));
	num sin_theta = sqrt(1 - cos_theta * cos_theta);
	
	// map that new vector into the new basis
	vector3 A(cos_phi * sin_theta, sin_phi * sin_theta, cos_theta);
	set(0, 0, 0);
	add_scaled(U, U.dot(A));
	add_scaled(V, V.dot(A));
	add_scaled(W, W.dot(A));
	return *this;
}
