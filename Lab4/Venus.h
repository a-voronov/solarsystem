#pragma once

#include "Planet.h"

class Venus : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getInitialInclination();
	double			getAxialTiltAngle();

public:
	Venus(void);
	Venus(double depthValue);
	~Venus(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};