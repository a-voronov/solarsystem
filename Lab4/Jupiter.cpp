#include "StdAfx.h"
#include "Jupiter.h"


Jupiter::Jupiter(void) : Planet() { }

Jupiter::Jupiter(double depthValue) : Planet(depthValue) { }

Jupiter::~Jupiter(void) { }

double Jupiter::getRadius()
{
	return 0.6;
}

coord Jupiter::getPathToOrbitCenter()
{
	return coord(5.0, 0.0, 0.0);
}

double Jupiter::getOrbitPeriod()
{
	return 4333.0;
}

double Jupiter::getSpinPeriod()
{
	return 0.4;
}

LPCWSTR Jupiter::getImageName()
{
	return TEXT("Bitmaps/jupitermap.bmp");
}

rotationCoord Jupiter::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Jupiter::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Jupiter::getAxialTiltAngle()
{
	return 3.13;
}
