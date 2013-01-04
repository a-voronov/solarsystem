#pragma once

#include "SphereSpaceObject.h"

class Star : public SphereSpaceObject
{
public:
	virtual ~Star(void) = 0;

	// Star can have:
	// - intensity of light
	// - 
	// Star can do:
	// - shine (be source of light)
};

