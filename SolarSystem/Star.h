#pragma once

#include "SphereSpaceObject.h"

class Star : public SphereSpaceObject
{
public:
	Star(void) : SphereSpaceObject() { }
	Star(double depthValue) : SphereSpaceObject(depthValue) { }
	virtual ~Star(void) = 0;

	// Star can have:
	// - intensity of light
	// - 
	// Star can do:
	// - shine (be source of light)
};

