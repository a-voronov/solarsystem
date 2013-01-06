#pragma once

#include "Planet.h"

class Saturn : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getAxialTiltAngle();

public:
	Saturn(void);
	Saturn(double depthValue);
	~Saturn(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
