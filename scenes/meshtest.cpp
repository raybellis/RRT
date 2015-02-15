#include <iostream>
#include <iomanip>
#include <cmath>
#include <csignal>
#include <unistd.h>

#include <rrt/rrt.h>
#include <rrt/camera.h>
#include <rrt/scene.h>
#include <rrt/renderer.h>

#include <primitive/plane.h>
#include <primitive/sphere.h>
#include <primitive/mesh.h>

#include <shader/stochastic.h>
#include <shader/hdri.h>

int main(int argc, char * const argv[]) {

	point3 eye(-2, 1, -3);
	point3 center(0, 0, 0);
	camera camera(eye, center);
	camera.fov(30);

	scene	world;

	plane	floor;
	floor.shader(new Shader::diffuse(world, colour(1.0)));
	floor.translate(0, -0.37, 0);
	world += floor;

	sphere	sky;
	sky.scale(20);
	sky.shader(new Shader::constant(world, colour(2.0)));
	world += sky;

	surface def;
	mesh	obj("objects/Tank ABRAMS L N090511.3DS");
	obj.shader(new Shader::diffuse(world, colour(0.8)));
	world += obj;

	renderer *r;
	if (argc > 1) {
		r = new renderer(world, camera, argv[1]);
	} else {
		r = new renderer(world, camera, 1440, 900);
	}

	signal(SIGINT, &renderer::stop_all);
	r->add_output_job(&renderer::write_ppm16, "meshtest.ppm", 8);
	r->add_output_job(&renderer::write_rrt, "meshtest.rrt", 8);
	r->start();
}
