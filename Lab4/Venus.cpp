#include "StdAfx.h"
#include "Venus.h"


Venus::Venus(void) : Planet() { }

Venus::Venus(double depthValue) : Planet(depthValue) { }

Venus::~Venus(void) { }

double Venus::getRadius()
{
	return 0.18;
}

coord Venus::getPathToOrbitCenter()
{
	return coord(2.0, 0.0, 0.0);
}

double Venus::getOrbitPeriod()
{
	return 225.0;
}

double Venus::getSpinPeriod()
{
	return -243.0;
}

LPCWSTR Venus::getImageName()
{
	return TEXT("Bitmaps/venusmap.bmp");
}

rotationCoord Venus::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Venus::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Venus::getAxialTiltAngle()
{
	return 177.3;
}
