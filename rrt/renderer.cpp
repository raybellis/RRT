/*
 *  renderer.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 20/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#include <cstdio>
#include <arpa/inet.h>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <iomanip>

#include "renderer.h"

#include "scene.h"
#include "camera.h"
#include "math.h"

std::set<renderer*> renderer::s_running;

renderer::renderer(scene& scene, camera& camera, const int _w, const int _h) :
	m_scene(scene), m_camera(camera), m_frame(0), w(_w), h(_h)
{
	colours = new colour[w * h];
	camera.aspect(w, h);
}

renderer::renderer(scene& scene, camera& camera, const std::string& filename) :
	m_scene(scene), m_camera(camera), m_frame(0)
{
	FILE *fp = fopen(filename.c_str(), "rb");
	::fread(&w, sizeof(w), 1, fp);
	::fread(&h, sizeof(h), 1, fp);
	::fread(&m_frame, sizeof(m_frame), 1, fp);
	colours = new colour[w * h];
	::fread(colours, sizeof(colour), w * h, fp);
	::fclose(fp);

	camera.aspect(w, h);
}

renderer::~renderer()
{
	delete[] colours;
}

void renderer::add_output_job(job_handler handler, const std::string& filename, unsigned int freq)
{
	job_entry		entry{handler, filename, freq};
	m_jobs.push_back(entry);
}

colour renderer::trace_pixel(int px, int py)
{
	// add some jitter
	double dx = px + math::random_ex() - 0.5;
	double dy = py + math::random_ex() - 0.5;
	
	// convert to camera coordinates
	double x = (dx / w) - 0.5;
	double y = 0.5 - (dy / h);
	
	// and trace it
	ray r = m_camera.cast_ray(x, y);
	return m_scene.trace(r);
}

void renderer::finish_frame(const colour *c)
{
	// copy frame details
	for (unsigned int i = 0, n = w * h; i < n; ++i) {
		colours[i] += c[i];
	}

	++m_frame;
	std::cout << std::setw(6) << m_frame << "\r" << std::flush;

	// call any registered output jobs
	for (auto job : m_jobs) {
		if (m_frame % job.freq == 0) {
			job.handler(*this, job.filename);
		}
	}
}

void renderer::trace_forever()
{
	colour *c = new colour[w * h];
	while (!m_shutdown) {
		int i = 0;
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				c[i++] = trace_pixel(x, y);
			}
		}
		finish_frame(c);
	}
	delete[] c;
}

void renderer::start(int maxthreads)
{
	if (s_running.count(this)) {
		throw std::runtime_error("renderer instance already started");
	} else {
		s_running.insert(this);
	}

	int ncpu = boost::thread::hardware_concurrency();
	int nthreads = (maxthreads > 0) ? std::min(maxthreads, ncpu) : ncpu;

	boost::thread_group group;
	boost::thread* threads[nthreads];

	for (int i = 0; i < nthreads; ++i) {
		threads[i] = new boost::thread(&renderer::trace_forever, this);
		group.add_thread(threads[i]);
	}

	group.join_all();
	s_running.erase(this);
}

void renderer::stop()
{
	std::cerr << "\nshutting down..." << std::endl;
	m_jobs.empty();
	m_shutdown = true;
}

void renderer::stop_all(int)
{
	for (auto r : s_running) {
		r->stop();
	}
}

void renderer::write_ppm(const std::string& filename)
{
	FILE *fp = ::fopen(filename.c_str(), "wb");
	::fprintf(fp, "P6\n%d %d\n255\n", w, h);
	
	int n = w * h;
	for (int i = 0; i < n; ++i) {
		colour c = colours[i];
		c *= 1.0 / m_frame;
		c.clamp();
		uint8_t buf[3];
		buf[0] = c.r() * 255;
		buf[1] = c.g() * 255;
		buf[2] = c.b() * 255;
		::fwrite(buf, sizeof(buf[0]), 3, fp);
	}
	::fclose(fp);
}

void renderer::write_ppm16(const std::string& filename)
{
	FILE *fp = ::fopen(filename.c_str(), "wb");
	::fprintf(fp, "P6\n%d %d\n65535\n", w, h);
	
	int n = w * h;
	for (int i = 0; i < n; ++i) {
		colour c = colours[i];
		c *= 1.0 / m_frame;
		c.clamp();
		uint16_t buf[3];
		buf[0] = htons(c.r() * 65535);
		buf[1] = htons(c.g() * 65535);
		buf[2] = htons(c.b() * 65535);
		::fwrite(buf, sizeof(buf[0]), 3, fp);
	}
	::fclose(fp);
}

void renderer::write_rrt(const std::string& filename)
{
	FILE *fp = ::fopen(filename.c_str(), "wb");
	::fwrite(&w, sizeof(w), 1, fp);
	::fwrite(&h, sizeof(h), 1, fp);
	::fwrite(&m_frame, sizeof(m_frame), 1, fp);
	::fwrite(colours, sizeof(colour), w * h, fp);
	::fclose(fp);
}
