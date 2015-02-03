/*
 *  core/camera.h
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_CAMERA_H
#define __CORE_CAMERA_H

#include "geom.h"
#include "ray.h"

//---------------------------------------------------------

class camera {

private: // hidden default ctor
	camera();
	
protected:
	point3					eye;
	point3					center;
	
	vector3					up;
	vector3					right;
	vector3					view;
	
	double					m_distance;
	double					m_tanf;
	double					m_fovy;
	double					m_aspect;
	double					m_aperture;

protected:
	void					recalc();

public:
							camera(const point3& eye, const point3& center);
							camera(const point3& eye, const point3& center, const vector3& up);
	
public:
	void					fov(double fovy);
	void					aspect(double aspect);
	void					aspect(int w, int h);
	void					aperture(double aperture);
	virtual ray				cast_ray(double x, double y) const;

};

//---------------------------------------------------------

#endif // __CORE_CAMERA_H
