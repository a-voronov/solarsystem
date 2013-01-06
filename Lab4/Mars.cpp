#include "StdAfx.h"
#include "Mars.h"


Mars::Mars(void) : Planet() { }

Mars::Mars(double depthValue) : Planet(depthValue) { }

Mars::~Mars(void) { }

double Mars::getRadius()
{
	return 0.3;
}

coord Mars::getPathToOrbitCenter()
{
	return coord(3.5, 0.0, 0.0);
}

double Mars::getOrbitPeriod()
{
	return 686.565;
}

double Mars::getSpinPeriod()
{
	return 1.026;
}

LPCWSTR Mars::getImageName()
{
	return TEXT("Bitmaps/marsmap.bmp");
}

rotationCoord Mars::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Mars::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Mars::getAxialTiltAngle()
{
	return 25.19;
}
