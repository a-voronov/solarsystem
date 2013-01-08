#include "StdAfx.h"
#include "Moon.h"


Moon::Moon(void) : Satellite() { }

Moon::Moon(double depthValue, Planet *planet) : Satellite(depthValue, planet) { }

Moon::~Moon(void) { }

double Moon::getRadius()
{
	return 0.04;
}

coord Moon::getPathToOrbitCenter()
{
	return coord(0.5, 0.0, 0.0);
}

double Moon::getOrbitPeriod()
{
	return 27.32166;
}

double Moon::getSpinPeriod()
{
	return 27.32166;
}

LPCWSTR Moon::getImageName()
{
	return TEXT("Bitmaps/moonmap.bmp");
}

rotationCoord Moon::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Moon::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Moon::getInitialInclination()
{
	return 25;
}

double Moon::getAxialTiltAngle()
{
	return 1.5424;
}
