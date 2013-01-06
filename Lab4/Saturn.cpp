#include "StdAfx.h"
#include "Saturn.h"


Saturn::Saturn(void) : Planet() { }

Saturn::Saturn(double depthValue) : Planet(depthValue) { }

Saturn::~Saturn(void) { }

double Saturn::getRadius()
{
	return 0.5;
}

coord Saturn::getPathToOrbitCenter()
{
	return coord(7.0, 0.0, 0.0);
}

double Saturn::getOrbitPeriod()
{
	return 10752.9;
}

double Saturn::getSpinPeriod()
{
	return 0.426;
}

LPCWSTR Saturn::getImageName()
{
	return TEXT("Bitmaps/saturnmap.bmp");
}

rotationCoord Saturn::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Saturn::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Saturn::getAxialTiltAngle()
{
	return 26.73;
}
