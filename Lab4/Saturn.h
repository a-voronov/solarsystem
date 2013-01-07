#pragma once

#include "Planet.h"

class Saturn : public Planet
{
protected:
	BitmapBits		ringImage;

	LPCWSTR			getImageName();
	coord			getPathToOrbitCenter();
	rotationCoord	getSpinRotationCoord();
	rotationCoord	getOrbitRotationCoord();
	double			getInitialInclination();
	double			getAxialTiltAngle();
	void			drawRing(void);

public:
	Saturn(void);
	Saturn(double depthValue);
	~Saturn(void);

	double getRadius();
	double getSpinPeriod();
	double getOrbitPeriod();
	void   initTextures(void);
	void   draw(void);
};
