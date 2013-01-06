#include "StdAfx.h"
#include "Pluto.h"


Pluto::Pluto(void) : Planet() { }

Pluto::Pluto(double depthValue) : Planet(depthValue) { }

Pluto::~Pluto(void) { }

double Pluto::getRadius()
{
	return 0.05;
}

coord Pluto::getPathToOrbitCenter()
{
	return coord(10.0, 0.0, 0.0);
}

double Pluto::getOrbitPeriod()
{
	return 90800.0;
}

double Pluto::getSpinPeriod()
{
	return -6.0;
}

LPCWSTR Pluto::getImageName()
{
	return TEXT("Bitmaps/Plutomap.bmp");
}

rotationCoord Pluto::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Pluto::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Pluto::getAxialTiltAngle()
{
	return 119.591;
}
