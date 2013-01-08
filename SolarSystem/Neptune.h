#pragma once

#include "Planet.h"

class Neptune : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getInitialInclination();
	double			getAxialTiltAngle();

public:
	Neptune(void);
	Neptune(double depthValue);
	~Neptune(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
