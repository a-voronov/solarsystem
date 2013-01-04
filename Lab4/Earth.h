#pragma once

#include "Planet.h"

class Earth : public Planet
{
protected:
	LPCWSTR			getImageName();
	double			getRadius();
	double			getSpinPeriod();
	double			getOrbitPeriod();
	coord			getDistanceToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	rotationCoord	getInitRotationCoord();

public:
	Earth(void);
	~Earth(void);
};

