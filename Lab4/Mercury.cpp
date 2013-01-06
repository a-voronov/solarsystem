#include "StdAfx.h"
#include "Mercury.h"


Mercury::Mercury(void) : Planet() { }

Mercury::Mercury(double depthValue) : Planet(depthValue) { }

Mercury::~Mercury(void) { }

double Mercury::getRadius()
{
	return 0.1;
}

coord Mercury::getPathToOrbitCenter()
{
	return coord(1.5, 0.0, 0.0);
}

double Mercury::getOrbitPeriod()
{
	return 88;
}

double Mercury::getSpinPeriod()
{
	return 59;
}

LPCWSTR Mercury::getImageName()
{
	return TEXT("Bitmaps/mercurymap.bmp");
}

rotationCoord Mercury::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Mercury::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Mercury::getAxialTiltAngle()
{
	return 0.03587;
}
