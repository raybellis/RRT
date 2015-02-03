/*
 *  core/math.h
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_MATH_H
#define __CORE_MATH_H

#include <cstdlib>

namespace math {

	const double pi = 3.141592653589793238462643383279502884;
	const double one_over_pi = 1.0 / pi;
	const double one_over_2pi = 0.5 / pi;

	const double epsilon = 1e-7;

	double deg2rad(double val);
	double clamp(double val, double min = 0.0, double max = 1.0);
	double random();
	double random_ex();

}

#endif // __CORE_MATH_H
