/*
 *  camera.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <cmath>
#include "camera.h"
#include "math.h"

camera::camera()
{
}

camera::camera(const point3& _eye, const point3& _center) :
	eye(_eye), center(_center)
{
	up.set(0, 1, 0);
	fov(30);
	m_aspect = 4.0 / 3;

	recalc();
}

camera::camera(const point3& _eye, const point3& _center, const vector3& _up) :
	eye(_eye), center(_center), up(_up)
{
	fov(30);
	m_aspect = 4.0 / 3;

	recalc();
}

void camera::recalc()
{
	// renormalise the up vector
	up.normalise();
	
	// calculate unit view direction vector
	view = vector3(eye, center);
	m_distance = view.length();
	view.normalise();
	
	// and the right hand view vector
	right = vector3::cross(up, view);
	right.normalise();
	
	// and re-base the up vector (may not be normalised)
	up = vector3::cross(view, right);
}

void camera::fov(double fovy)
{
	m_fovy = math::deg2rad(fovy) / 2.0;
	m_tanf = tan(m_fovy);
}

void camera::aspect(double aspect)
{
	m_aspect = aspect;
}

void camera::aspect(int x, int y)
{
	m_aspect = (double)x / y;
}

void camera::aperture(double aperture)
{
	m_aperture = aperture;
}

ray camera::cast_ray(double x, double y) const
{
	point3 view(center);
	view.add_scaled(right, m_distance * m_tanf * m_aspect * x);
	view.add_scaled(up, m_distance * m_tanf * y);

	point3 lens(eye);
	if (m_aperture > 0) {
		double u = m_aperture * math::random();
		double v = 2.0 * math::pi * math::random();
		lens.add_scaled(right, u * cos(v));
		lens.add_scaled(up, u * sin(v));
	}

	vector3 dir(lens, view);
	dir.normalise();

	return ray(lens, dir, 0, 1.0);
}
