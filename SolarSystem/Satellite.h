#pragma once

#include "SphereSpaceObject.h"
#include "Planet.h"

class Satellite : public SphereSpaceObject
{
private:
	Planet *rotationPlanet;

protected:
	void setRotationPlanet(Planet *planet);

public:
	Satellite(void) : SphereSpaceObject() { }
	Satellite(double depthValue, Planet *planet);// : SphereSpaceObject(depthValue);
	virtual ~Satellite(void) = 0;
	
	Planet* getRotationPlanet(void);
	void draw(void);
};

