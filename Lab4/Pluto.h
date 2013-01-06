#pragma once

#include "Planet.h"

class Pluto : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getAxialTiltAngle();

public:
	Pluto(void);
	Pluto(double depthValue);
	~Pluto(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
