/*
 *  core/surface.h
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_SURFACE_H
#define __CORE_SURFACE_H

#include "rrt.h"

//---------------------------------------------------------

class surface {
	
protected:
	colour					m_diffuse;
	colour					m_ambient;
	colour					m_reflect;
	colour					m_transmit;
	float					m_ior;
	float					m_smooth;
	
public:
	surface();
	surface(const surface& rhs);
	surface& operator=(const surface& rhs);

public:
	const colour&			diffuse() const				{ return m_diffuse; }
	const colour&			ambient() const				{ return m_ambient; }
	const colour&			reflect() const				{ return m_reflect; }
	const colour&			transmit() const			{ return m_transmit; }
	float					ior() const					{ return m_ior; }
	float					smooth() const				{ return m_smooth; }
	
public:
	void					diffuse(const colour& c)	{ m_diffuse = c; }
	void					ambient(const colour& c)	{ m_ambient = c; }
	void					reflect(const colour& c)	{ m_reflect = c; }
	void					transmit(const colour& c)	{ m_transmit = c; }
	void					ior(float f)				{ m_ior = f; }
	void					smooth(float f)				{ m_smooth = f; }
};

//---------------------------------------------------------

#endif // __CORE_SURFACE_H
