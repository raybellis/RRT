/*
 *  primitive/mesh.h
 *  RRT
 *
 *  Created by Ray Bellis on 08/02/2015.
 *  Copyright 2015 Ray Bellis. All rights reserved.
 *
 */

#ifndef __PRIMITIVE_MESH_H
#define __PRIMITIVE_MESH_H

#include <list>

#include <rrt/primitive.h>
#include "triangle.h"
#include "cube.h"

class mesh : public compound {

protected:
	cube				m_cube;	// for bounds tests

public:
	mesh(const std::string& filename);

public:
	virtual int intersect(const ray& ray_in, hits& hits) const;

};

#endif // __PRIMITIVE_MESH_H
