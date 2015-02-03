/*
 *  hit.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 29/08/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#include "hit.h"
#include "primitive.h"

hit::hit(point3::num distance, const primitive *primitive) :
	m_distance(distance), m_primitive(primitive), m_transform(&primitive->transform())
{
}

hit::hit(const hit& rhs)
{
	m_distance = rhs.m_distance;
	m_primitive = rhs.m_primitive;
	m_transform = rhs.m_transform;
}

hit& hit::operator=(const hit& rhs)
{
	m_distance = rhs.m_distance;
	m_primitive = rhs.m_primitive;
	m_transform = rhs.m_transform;
	return *this;
}

bool hit::operator<(const hit& rhs) const
{
	return (m_distance < rhs.m_distance);
}
