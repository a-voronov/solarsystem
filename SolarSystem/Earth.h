#pragma once

#include "Planet.h"

class Earth : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getInitialInclination();
	double			getAxialTiltAngle();

public:
	Earth(void);
	Earth(double depthValue);
	~Earth(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
