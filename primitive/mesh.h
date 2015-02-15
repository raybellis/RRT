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

class mesh : public compound {

public:
	mesh(const std::string& filename);

};

#endif // __PRIMITIVE_MESH_H
