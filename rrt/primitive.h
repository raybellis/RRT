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

public:
	virtual int						intersect(const ray& ray, hits& hits) const = 0;
	virtual vector3					normal(const point3& point) const = 0;
	virtual uvcoord					uvmap(const point3& point) const = 0;

public:
	virtual void					set_shader(const shader& s) { m_shader = &s; }
	virtual void					set_shader(const shader* s) { m_shader = s; }
	virtual colour					shade(const ray& r, const point3& p, const vector3& n) const;
	
public:
	void							transform(const transform& t);
	const class transform&			transform() const { return m_transform; }

};

typedef std::list<const primitive*>	prims;

//---------------------------------------------------------

class compound : public primitive {

protected:
	prims							prims;

public:
	compound();

public:
	virtual	int						intersect(const ray& ray, hits& hits) const;
	virtual vector3					normal(const point3& point) const;
	virtual uvcoord					uvmap(const point3& point) const;

	void							operator+=(const primitive& p) { prims.push_back(&p); }
	void							operator+=(const primitive* p) { prims.push_back(p); }
};

//---------------------------------------------------------

#endif // __CORE_PRIMITIVE_H