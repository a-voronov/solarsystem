#pragma once

#include "SphereSpaceObject.h"

class Planet : public SphereSpaceObject
{
public:
	Planet(void) : SphereSpaceObject() { }
	Planet(double depthValue) : SphereSpaceObject(depthValue) { }
	virtual ~Planet(void) = 0;

	// Planet can:
	// - have array of moons
};

