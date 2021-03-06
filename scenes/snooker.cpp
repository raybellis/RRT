#include <iostream>
#include <iomanip>
#include <cmath>
#include <csignal>
#include <unistd.h>

#include <rrt/rrt.h>
#include <rrt/camera.h>
#include <rrt/scene.h>
#include <rrt/renderer.h>

#include <primitive/sphere.h>
#include <primitive/plane.h>

#include <shader/stochastic.h>
#include <shader/hdri.h>

int main(int argc, char * const argv[]) {

	point3 eye(-8, 8, -12);
	point3 center(0, 1, 2);
	camera camera(eye, center);
	camera.fov(55);
	camera.aperture(0.25);

	scene	world;
	plane	floor;

	surface	 def;
	def.reflect(0.15);
	def.smooth(0.01);

	// red balls
	compound pack;
	{
		surface	 red = def;
		red.diffuse(colour(0.85, 0.2, 0.2));

		shader *s = new Shader::stochastic(world, red);

		double dx = 2.0;
		double dz = ::sqrt(3.0);

		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j <= i; ++j) {

				double x = (j - (i / 2.0)) * dx;
				double z = (4 - i) * dz;

				primitive *ball = new sphere();
				ball->translate(x, 1, z);
				ball->shader(s);
				pack += ball;
			}
		}
		world += pack;
	}

	// pink ball
	{
		surface	 pink  = def;
		pink.diffuse(colour(0.85, 0.5, 0.5));

		double z = 4 * ::sqrt(3.0) + 2;
		primitive* ball = new sphere();
		ball->translate(0, 1, z);
		ball->shader(new Shader::stochastic(world, pink));
		world += ball;
	}

	// black ball
	{
		surface	 black = def;
		black.diffuse(0.1);

		primitive* ball = new sphere();
		ball->translate(0, 1, -3);
		ball->shader(new Shader::stochastic(world, black));
		world += ball;
	}

	// baize
	{
		floor.shader(new Shader::diffuse(world, colour(0.3, 0.7, 0.4)));
		world += floor;
	}

	// sky
	{
		image *img = new image("hdri/hallway1_color-077ma.jpg");
		primitive* sky = new sphere();
		sky->scale(50);
		sky->shader(new Shader::hdri(world, img, 1.6));
		world += sky;
	}

	renderer *r;
	if (argc > 1) {
		r = new renderer(world, camera, argv[1]);
	} else {
		r = new renderer(world, camera, 1440, 900);
	}

	signal(SIGINT, &renderer::stop_all);
	r->add_output_job(&renderer::write_ppm16, "snooker.ppm", 8);
	r->add_output_job(&renderer::write_rrt, "snooker.rrt", 8);
	r->start();
}
