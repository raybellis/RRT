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
#include <functional>
#include <set>

//---------------------------------------------------------
// forward declarations 
class scene;
class camera;
class colour;
class renderer;

//---------------------------------------------------------

typedef std::function<void(renderer& r, const std::string&)> job_handler;

struct job_entry {
	job_handler						handler;
	std::string						filename;
	unsigned int					freq;
};

class renderer {

public:
	static std::set<renderer*>		s_running;

protected:
	const scene&					m_scene;
	const camera&					m_camera;
	std::atomic_int					m_frame{0};
	std::atomic_bool				m_shutdown{false};
	std::list<job_entry>			m_jobs;
	int								w, h;
	colour*							colours;

public:
	renderer(scene& scene, camera& camera, const int w, const int h);
	renderer(scene& scene, camera& camera, const std::string& filename);
	~renderer();

protected:
	void							finish_frame(colour *c);
	colour							trace_pixel(int px, int py);
	void							trace_forever();

public:
	void							start(int maxthreads = 0);
	void							stop();
	static void						stop_all(int);

public:	// output methods
	void							add_output_job(job_handler handler, const std::string& filename, unsigned int freq);
	void							write_ppm(const std::string& filename);
	void							write_ppm16(const std::string& filename);
	void							write_rrt(const std::string& filename);

};

//---------------------------------------------------------

#endif // __CORE_RENDERER_H
