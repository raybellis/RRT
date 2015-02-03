/*
 *  surface.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include "surface.h"

surface::surface() :
	m_diffuse(0.8), m_ambient(0), m_reflect(0), m_transmit(0),
	m_ior(1), m_smooth(0)
{
}

surface::surface(const surface& rhs) :
	m_diffuse(rhs.m_diffuse),
	m_ambient(rhs.m_ambient),
	m_reflect(rhs.m_reflect),
	m_transmit(rhs.m_transmit),
	m_ior(rhs.m_ior),
	m_smooth(rhs.m_smooth)
{
}

surface& surface::operator=(const surface& rhs)
{
	m_diffuse = rhs.m_diffuse;
	m_ambient = rhs.m_ambient;
	m_reflect = rhs.m_reflect;
	m_transmit = rhs.m_transmit;
	m_ior = rhs.m_ior;
	m_smooth = rhs.m_smooth;
	return *this;
}
