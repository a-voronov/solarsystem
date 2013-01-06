#pragma once

#include "Star.h"

class Sun : public Star
{
protected:
	LPCWSTR			getImageName();
	rotationCoord	getSpinRotationCoord();
	coord			getPathToOrbitCenter();
	rotationCoord	getOrbitRotationCoord();

public:
	Sun(void);
	Sun(double depthValue);
	~Sun(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};

