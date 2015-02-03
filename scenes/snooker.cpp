#include <iostream>
#include <iomanip>
#include <cmath>
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
				ball->transform(transform::translate(x, 1, z));
				ball->set_shader(s);
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
		ball->transform(transform::translate(0, 1, z));
		ball->set_shader(new Shader::stochastic(world, pink));
		world += ball;
	}

	// black ball
	{
		surface	 black = def;
		black.diffuse(0.1);

		primitive* ball = new sphere();
		ball->transform(transform::translate(0, 1, -3));
		ball->set_shader(new Shader::stochastic(world, black));
		world += ball;
	}

	// baize
	{
		floor.set_shader(new Shader::diffuse(world, colour(0.3, 0.7, 0.4)));
		world += floor;
	}

	// sky
	{
		image *img = new image("hdri/hallway1_color-077ma.jpg");
		primitive* sky = new sphere();
		sky->transform(transform::scale(50));
		sky->set_shader(new Shader::hdri(world, img));
		world += sky;
	}

	renderer *r;
	if (argc > 1) {
		r = new renderer(world, camera, argv[1]);
	} else {
		r = new renderer(world, camera, 1440, 900);
	}

	r->start();

	int i = 0;
	while (true) {
		std::cout << std::setw(6) << r->frame() << "\r" << std::flush;
		if ((++i % 60) == 0) {
			r->write_ppm16("snooker.ppm");
			r->write_rrt("snooker.rrt");
		}
		sleep(1);
	}
	std::cout << std::endl;
}
