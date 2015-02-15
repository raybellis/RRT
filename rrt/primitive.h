/*
 *  core/primitive.h
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_PRIMITIVE_H
#define __CORE_PRIMITIVE_H

#include <list>

#include "geom.h"
#include "transform.h"
#include "shader.h"
#include "ray.h"
#include "hit.h"

//---------------------------------------------------------
// forward declarations
//---------------------------------------------------------

class primitive {

protected:
	const shader*					m_shader;
	transform						m_transform;

public:
	primitive();
	virtual ~primitive();

public:
	virtual int						intersect(const ray& ray, hits& hits) const = 0;
	virtual vector3					normal(const point3& point, const hitinfo *hi = nullptr) const = 0;
	virtual uvcoord					uvmap(const point3& point) const = 0;

public:
	virtual void					shader(const Shader::base& s) { m_shader = &s; }
	virtual void					shader(const Shader::base* s) { m_shader = s; }
	virtual colour					shade(const ray& r, const point3& p, const vector3& n) const;
	
public:
	const class transform&			transform() const { return m_transform; }
	void							transform(const class transform& t);

	void							translate(double x, double y, double z);
	void							translate(const vector3& v);
	void							scale(double x, double y, double z);
	void							scale(double s);
	void							rotate(double x, double y, double z, double theta);
	void							rotate(const vector3& v, double theta);
	void							rotate_x(double theta);
	void							rotate_y(double theta);
	void							rotate_z(double theta);

};

typedef std::list<primitive*>		prims;

//---------------------------------------------------------

class compound : public primitive {

protected:
	prims							prims;

public:
	compound();

public:
	virtual	int						intersect(const ray& ray, hits& hits) const;
	virtual vector3					normal(const point3& point, const hitinfo *hi = nullptr) const;
	virtual uvcoord					uvmap(const point3& point) const;

	virtual void					shader(const Shader::base& s);
	virtual void					shader(const Shader::base* s);

	void							operator+=(primitive& p) { prims.push_back(&p); }
	void							operator+=(primitive* p) { prims.push_back(p); }
};

//---------------------------------------------------------

#endif // __CORE_PRIMITIVE_H
