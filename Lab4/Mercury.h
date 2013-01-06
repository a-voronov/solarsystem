#pragma once

#include "Planet.h"

class Mercury : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getAxialTiltAngle();

public:
	Mercury(void);
	Mercury(double depthValue);
	~Mercury(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
