#pragma once

#include "Planet.h"

class Uranus : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getInitialInclination();
	double			getAxialTiltAngle();

public:
	Uranus(void);
	Uranus(double depthValue);
	~Uranus(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
