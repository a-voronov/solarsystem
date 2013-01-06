#pragma once

#include "Planet.h"

class Mars : public Planet
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getAxialTiltAngle();

public:
	Mars(void);
	Mars(double depthValue);
	~Mars(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};
