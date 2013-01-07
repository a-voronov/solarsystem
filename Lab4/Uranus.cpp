#include "StdAfx.h"
#include "Uranus.h"


Uranus::Uranus(void) : Planet() { }

Uranus::Uranus(double depthValue) : Planet(depthValue) { }

Uranus::~Uranus(void) { }

double Uranus::getRadius()
{
	return 0.3;
}

coord Uranus::getPathToOrbitCenter()
{
	return coord(9.9, 0.0, 0.0);
}

double Uranus::getOrbitPeriod()
{
	return 30776.8;
}

double Uranus::getSpinPeriod()
{
	return -0.718;
}

LPCWSTR Uranus::getImageName()
{
	return TEXT("Bitmaps/uranusmap.bmp");
}

rotationCoord Uranus::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Uranus::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Uranus::getInitialInclination()
{
	return 1.0;
}

double Uranus::getAxialTiltAngle()
{
	return 97.77;
}
