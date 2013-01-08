#pragma once

#include "satellite.h"

class Moon : public Satellite
{
protected:
	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getInitialInclination();
	double			getAxialTiltAngle();

public:
	Moon(void);
	Moon(double depthValue, Planet *planet);
	~Moon(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
};

