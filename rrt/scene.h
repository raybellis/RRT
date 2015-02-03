/*
 *  core/scene.h
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_SCENE_H
#define __CORE_SCENE_H

#include "primitive.h"

class scene : public compound {

protected:
	colour					m_background;

public:
	scene();

public:
	colour					trace(const ray& r) const;

};

#endif // __CORE_SCENE_H
