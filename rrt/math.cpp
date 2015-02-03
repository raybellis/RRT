/*
 *  math.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 29/08/2014.
 *  Copyright 2014 Ray Bellis. All rights reserved.
 *
 */

#include "math.h"

static const double _cvt_deg2rad = math::pi / 180.0;
static const double _rand_inc = 1.0 / RAND_MAX;
static const double _rand_ex  = 1.0 / (RAND_MAX + 1.0);

namespace math {


	double deg2rad(double val) {
		return val * _cvt_deg2rad;
	}

	double clamp(double val, double min, double max) {
		return (val < min) ? min : ((val > max) ? max : val);
	}

	// random in range [0, 1]
	double random() {
		return ::random() * _rand_inc;
	}

	// random in range [0, 1)
	double random_ex() {
		return ::random() * _rand_ex;
	}
}
