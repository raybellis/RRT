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
#include <primitive/cube.h>

#include <shader/stochastic.h>
#include <shader/checker.h>

int main(int argc, char * const argv[]) {

	point3 eye(0, 0, -20);
	point3 center(0, 0, 0);
	camera camera(eye, center);
	camera.fov(60);
	camera.aperture(0.25);

	scene world;
	plane floor, right, left, back, ceiling;

	surface		 black_tile;
	black_tile.diffuse(0.1);
	black_tile.reflect(0.05);
	black_tile.smooth(0.01);

	surface		 white_tile;
	white_tile.diffuse(0.7);
	white_tile.reflect(0.05);
	white_tile.smooth(0.01);

	floor.shader(new Shader::checker(world,
		new Shader::stochastic(world, black_tile),
		new Shader::stochastic(world, white_tile)));
	floor.rotate_y(math::pi / 4.0);
	floor.scale(2.0);
	floor.translate(0, -4, 0);
	world += floor;

	left.rotate_z(-math::pi / 2.0);
	left.translate(-4, 0, 0);
	left.shader(new Shader::diffuse(world, colour(1, 0.5, 0.5)));
	world += left;

	right.rotate_z(math::pi / 2.0);
	right.translate(4, 0, 0);
	right.shader(new Shader::diffuse(world, colour(0.5, 1, 0.5)));
	world += right;

	back.rotate_x(-math::pi / 2.0);
	back.translate(0, 0, 4);
	back.shader(new Shader::diffuse(world, 0.8));
	world += back;

	ceiling.rotate_x(math::pi);
	ceiling.translate(0, 4, 0);
	ceiling.shader(new Shader::diffuse(world, 1.0));
	world += ceiling;

	cube		light1;
	light1.scale(0.001, 1.6, 2);
	light1.translate(-4, 1, 0);
	light1.shader(new Shader::constant(world, 10.0));
	world += light1;

	cube		light2;
	light2.scale(0.001, 1.6, 2);
	light2.translate(4, 1, 0);
	light2.shader(new Shader::constant(world, 10.0));
	world += light2;

	surface		crystal;
	crystal.diffuse(0.1);
	crystal.reflect(0.1);
	crystal.transmit(0.8);
	crystal.ior(1.6);

	sphere		ball;
	ball.scale(1.4);
	ball.translate(2.6, -2.6, -2);
	ball.shader(new Shader::stochastic(world, crystal));
	world += ball;

	surface		gold;
	gold.reflect(colour(0.5, 0.45, 0.25));
	gold.diffuse(colour(0.5, 0.45, 0.25));
	gold.smooth(0.05);

	sphere		ball2;
	ball2.translate(-2.6, -3, -1);
	ball2.shader(new Shader::stochastic(world, gold));
	world += ball2;

	surface		silver;
	silver.reflect(0.7);
	silver.diffuse(0.3);
	silver.smooth(0.05);

	cube		box;
	box.rotate_y(math::pi / 7.0);
	box.scale(1.2);
	box.translate(0, -2.8, 1.8);
	box.shader(new Shader::stochastic(world, silver));
	world += box;

	renderer *r;
	if (argc > 1) {
		r = new renderer(world, camera, argv[1]);
	} else {
		r = new renderer(world, camera, 1024, 1024);
	}

	signal(SIGINT, &renderer::stop_all);
	r->add_output_job(&renderer::write_ppm16, "cornell.ppm", 8);
	r->add_output_job(&renderer::write_rrt, "cornell.rrt", 8);
	r->start();
}
