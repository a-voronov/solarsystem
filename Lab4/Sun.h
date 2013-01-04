#pragma once

#include "Star.h"

class Sun : public Star
{
protected:
	LPCWSTR			getImageName();
	double			getRadius();
	double			getSpinPeriod();
	double			getOrbitPeriod();
	rotationCoord	getSpinRotationCoord();
	coord			getDistanceToOrbitCenter();
	rotationCoord	getOrbitRotationCoord();
	double			getSphereSlices();
	double			getSphereStacks();

public:
	Sun(void);
	~Sun(void);
};

