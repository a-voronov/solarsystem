#pragma once

#include "Planet.h"

class Jupiter : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getAxialTiltAngle();

public:
	Jupiter(void);
	Jupiter(double depthValue);
	~Jupiter(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
