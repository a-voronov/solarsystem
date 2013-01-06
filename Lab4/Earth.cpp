#include "StdAfx.h"
#include "Earth.h"


Earth::Earth(void) : Planet() { }

Earth::Earth(double depthValue) : Planet(depthValue) { }

Earth::~Earth(void) { }

double Earth::getRadius()
{
	return 0.18;
}

coord Earth::getPathToOrbitCenter()
{
	return coord(3.0, 0.0, 0.0);
}

double Earth::getOrbitPeriod()
{
	return 365.0;
}

double Earth::getSpinPeriod()
{
	return 1.0;
}

LPCWSTR Earth::getImageName()
{
	return TEXT("Bitmaps/earthmap.bmp");
}

rotationCoord Earth::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Earth::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Earth::getAxialTiltAngle()
{
	return 23.0;
}
