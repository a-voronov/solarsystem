#include "StdAfx.h"
#include "Neptune.h"


Neptune::Neptune(void) : Planet() { }

Neptune::Neptune(double depthValue) : Planet(depthValue) { }

Neptune::~Neptune(void) { }

double Neptune::getRadius()
{
	return 0.3;
}

coord Neptune::getPathToOrbitCenter()
{
	return coord(11.2, 0.0, 0.0);
}

double Neptune::getOrbitPeriod()
{
	return 60152.0;
}

double Neptune::getSpinPeriod()
{
	return 0.671;
}

LPCWSTR Neptune::getImageName()
{
	return TEXT("Bitmaps/Neptunemap.bmp");
}

rotationCoord Neptune::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Neptune::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Neptune::getInitialInclination()
{
	return 2.0;
}

double Neptune::getAxialTiltAngle()
{
	return 28.32;
}
