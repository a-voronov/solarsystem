#include "StdAfx.h"
#include "Earth.h"


Earth::Earth(void) 
{ 
	this->setOrbitRotationAngle(0.0);
	this->setSpinRotationAngle(0.0);
}

Earth::~Earth(void) { /* destructor body */ }

LPCWSTR Earth::getImageName()
{
	return TEXT("earth.bmp");
}

double Earth::getRadius()
{
	return 0.3;
}

double Earth::getSpinPeriod()
{
	return 1.0;
}

double Earth::getOrbitPeriod()
{
	return 365.0;
}

coord Earth::getDistanceToOrbitCenter()
{
	return coord(2.0, 0.0, 0.0);
}

rotationCoord Earth::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Earth::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Earth::getInitRotationCoord()
{
	return rotationCoord(23 + this->sphereDrawnAngle, 1.0, 0.0, 0.0);
}