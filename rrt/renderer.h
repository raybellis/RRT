/*
 *  core/renderer.h
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_RENDERER_H
#define __CORE_RENDERER_H

#include <atomic>
#include <string>

//---------------------------------------------------------
// forward declarations 
class scene;
class camera;
class colour;

//---------------------------------------------------------

class renderer {
	
protected:
	const scene&			m_scene;
	const camera&			m_camera;
	std::atomic_int			m_frame{0};
	std::atomic_bool		m_shutdown{false};
	int						w, h;

	colour*					colours;
	int*					counters;

public:
	renderer(scene& scene, camera& camera, const int w, const int h);
	renderer(scene& scene, camera& camera, const std::string& filename);
	~renderer();

protected:
	colour					trace_pixel(int px, int py);
	void					trace_forever();

public:
	void					start(int maxthreads = 0);

	int						frame();

public:	// output methods
	void					write_ppm(const std::string& filename);
	void					write_ppm16(const std::string& filename);
	void					write_rrt(const std::string& filename);

};

//---------------------------------------------------------

#endif // __CORE_RENDERER_H
