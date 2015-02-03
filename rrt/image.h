/*
 *  core/image.h
 *  RRT
 *
 *  Created by Ray Bellis on 21/05/2013.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_IMAGE_H
#define __CORE_IMAGE_H

#include <cstdio>
#include <string>
#include <gd.h>

#include "rrt.h"

class image {

protected:
	gdImagePtr					m_gd;

public:
	image(const std::string& filename);
	~image();

public:
	void read_png(const std::string& filename);
	void read_jpeg(const std::string& filename);
	void write_png(const std::string& filename);

public:
	const colour get_colour(const uvcoord& uv) const;
};

//---------------------------------------------------------

#endif // __CORE_IMAGE_H
