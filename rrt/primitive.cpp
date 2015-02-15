/*
 *  primitive.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <stdexcept>
#include "primitive.h"
#include "transform.h"
#include <shader/diffuse.h>

//----------------------------------------------------------

primitive::primitive() : m_shader(0)
{
}

primitive::~primitive()
{
}

colour primitive::shade(const ray& r, const point3& p, const vector3& n) const
{
	if (!m_shader) {
		throw std::runtime_error("no shader attached");
	}

	uvcoord uv = uvmap(m_transform.world2object(p));
	return m_shader->shade(r, p, n, uv);
};

void primitive::transform(const class transform& t)
{
	m_transform = t * m_transform;
}

void primitive::translate(double x, double y, double z)
{
	transform(transform::translate(x, y, z));
}

void primitive::translate(const vector3& v)
{
	transform(transform::translate(v));
}

void primitive::scale(double x, double y, double z)
{
	transform(transform::scale(x, y, z));
}

void primitive::scale(double s)
{
	transform(transform::scale(s));
}

void primitive::rotate(double x, double y, double z, double theta)
{
	transform(transform::rotate(x, y, z, theta));
}

void primitive::rotate(const vector3& v, double theta)
{
	transform(transform::rotate(v, theta));
}

void primitive::rotate_x(double theta)
{
	transform(transform::rotate_x(theta));
}

void primitive::rotate_y(double theta)
{
	transform(transform::rotate_y(theta));
}

void primitive::rotate_z(double theta)
{
	transform(transform::rotate_z(theta));
}

//----------------------------------------------------------

compound::compound() :
	prims()
{
}

int compound::intersect(const ray& ray_in, hits& hits) const
{
	int count = 0;
	for (auto p: prims) {
		const auto t = p->transform() * m_transform;
		auto ray_out = t.world2object(ray_in);
		count += p->intersect(ray_out, hits);
	}
	return count;
}

// this should never be invoked
vector3	compound::normal(const point3&, const hitinfo*) const
{
	throw std::runtime_error("compound::normal() called");
}

// this should never be invoked
uvcoord compound::uvmap(const point3&) const
{
	throw std::runtime_error("compound::uvmap() called");
}

void compound::shader(const Shader::base& s) {
	for (primitive *p: prims) {
		p->shader(s);
	}
}

void compound::shader(const Shader::base* s) {
	for (primitive *p: prims) {
		p->shader(s);
	}
}
