#pragma once

#include "SphereSpaceObject.h"

class Planet : public SphereSpaceObject
{
public:
	virtual ~Planet(void) = 0;

	// Planet can:
	// - have array of moons
};

