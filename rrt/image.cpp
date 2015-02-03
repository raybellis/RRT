/*
 *  image.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 21/05/2013.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <stdexcept>
#include <iostream>
#include <cstdio>

#include <boost/algorithm/string/predicate.hpp>

#include "image.h"

image::image(const std::string& filename) : m_gd(0)
{
	if (boost::algorithm::ends_with(filename, "jpg") ||
	    boost::algorithm::ends_with(filename, "jpeg"))
	{
		read_jpeg(filename);
	} else if (boost::algorithm::ends_with(filename, "png")) {
		read_png(filename);
	} else {
		throw std::runtime_error("image::image() called with unknown file type");
	}

	std::cout << "image " << filename << " loaded with resolution (" <<
			gdImageSX(m_gd) << ", " << gdImageSY(m_gd) << ")" << std::endl;
};

image::~image()
{
	if (m_gd) {
		gdImageDestroy(m_gd);
		m_gd = 0;
	}
};

void image::read_png(const std::string& filename)
{
	if (m_gd) {
		gdImageDestroy(m_gd);
	}

	FILE *f = fopen(filename.c_str(), "rb");
	m_gd = gdImageCreateFromPng(f);
	fclose(f);
};

void image::write_png(const std::string& filename)
{
	FILE *f = fopen(filename.c_str(), "wb");
	gdImagePng(m_gd, f);
	fclose(f);
};

void image::read_jpeg(const std::string& filename)
{
	if (m_gd) {
		gdImageDestroy(m_gd);
	}

	FILE *f = fopen(filename.c_str(), "rb");
	m_gd = gdImageCreateFromJpeg(f);
	fclose(f);
};

const colour image::get_colour(const uvcoord& uv) const
{

	int x = uv.x * gdImageSX(m_gd);
	int y = uv.y * gdImageSY(m_gd);
	int c = gdImageGetPixel(m_gd, x, y);

	return colour(gdImageRed(m_gd, c) / 255.0,
				  gdImageGreen(m_gd, c) / 255.0,
				  gdImageBlue(m_gd, c) / 255.0);
};
