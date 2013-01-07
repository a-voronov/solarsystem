#include "StdAfx.h"
#include "Sun.h"


Sun::Sun(void) : Star() { }

Sun::Sun(double depthValue) : Star(depthValue) { }

Sun::~Sun(void) { }

double Sun::getRadius() 
{
	return 1.0;
}

double Sun::getSpinPeriod()
{
	return 25.0;
}

double Sun::getOrbitPeriod() 
{
	return 0.0;
}

LPCWSTR	Sun::getImageName()
{
	return TEXT("Bitmaps/sunmap.bmp");
}

coord Sun::getPathToOrbitCenter() 
{
	return coord(0.0, 0.0, 0.0);
}

rotationCoord Sun::getSpinRotationCoord() 
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Sun::getOrbitRotationCoord()
{
	return rotationCoord(0.0, 0.0, 0.0, 0.0);
}

double Sun::getInitialInclination()
{
	return 0.0;
}

