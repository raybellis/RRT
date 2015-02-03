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

	floor.set_shader(new Shader::checker(world,
		new Shader::stochastic(world, black_tile),
		new Shader::stochastic(world, white_tile)));
	floor.transform(transform::rotate_y(math::pi / 4.0));
	floor.transform(transform::scale(2.0));
	floor.transform(transform::translate(0, -4, 0));
	world += floor;

	left.transform(transform::rotate_z(-math::pi / 2.0));
	left.transform(transform::translate(-4, 0, 0));
	left.set_shader(new Shader::diffuse(world, colour(1, 0.5, 0.5)));
	world += left;

	right.transform(transform::rotate_z(math::pi / 2.0));
	right.transform(transform::translate(4, 0, 0));
	right.set_shader(new Shader::diffuse(world, colour(0.5, 1, 0.5)));
	world += right;

	back.transform(transform::rotate_x(-math::pi / 2.0));
	back.transform(transform::translate(0, 0, 4));
	back.set_shader(new Shader::diffuse(world, 0.8));
	world += back;

	ceiling.transform(transform::rotate_x(math::pi));
	ceiling.transform(transform::translate(0, 4, 0));
	ceiling.set_shader(new Shader::diffuse(world, 1.0));
	world += ceiling;

	cube		light1;
	light1.transform(transform::scale(0.001, 1.6, 2));
	light1.transform(transform::translate(-4, 1, 0));
	light1.set_shader(new Shader::constant(world, 10.0));
	world += light1;

	cube		light2;
	light2.transform(transform::scale(0.001, 1.6, 2));
	light2.transform(transform::translate(4, 1, 0));
	light2.set_shader(new Shader::constant(world, 10.0));
	world += light2;

	surface		crystal;
	crystal.diffuse(0.1);
	crystal.reflect(0.1);
	crystal.transmit(0.8);
	crystal.ior(1.6);

	sphere		ball;
	ball.transform(transform::scale(1.4));
	ball.transform(transform::translate(2.6, -2.6, -2));
	ball.set_shader(new Shader::stochastic(world, crystal));
	world += ball;

	surface		gold;
	gold.reflect(colour(0.5, 0.45, 0.25));
	gold.diffuse(colour(0.5, 0.45, 0.25));
	gold.smooth(0.05);

	sphere		ball2;
	ball2.transform(transform::translate(-2.6, -3, -1));
	ball2.set_shader(new Shader::stochastic(world, gold));
	world += ball2;

	surface		silver;
	silver.reflect(0.7);
	silver.diffuse(0.3);
	silver.smooth(0.05);

	cube		box;
	box.transform(transform::rotate_y(math::pi / 7.0));
	box.transform(transform::scale(1.2));
	box.transform(transform::translate(0, -2.8, 1.8));
	box.set_shader(new Shader::stochastic(world, silver));
	world += box;

	renderer *r;
	if (argc > 1) {
		r = new renderer(world, camera, argv[1]);
	} else {
		r = new renderer(world, camera, 1024, 1024);
	}

	r->add_output_job(&renderer::write_ppm16, "cornell.ppm", 8);
	r->add_output_job(&renderer::write_rrt, "cornell.rrt", 8);
	r->start();
}
