#include "StdAfx.h"
#include "Satellite.h"


Satellite::~Satellite(void) { }

Satellite::Satellite(double depthValue, Planet *planet) : SphereSpaceObject(depthValue)
{
	this->setRotationPlanet(planet);
}

void Satellite::setRotationPlanet(Planet *planet)
{
	this->rotationPlanet = planet;
}

Planet* Satellite::getRotationPlanet(void)
{
	return this->rotationPlanet;
}

void Satellite::draw(void)
{
	glPushMatrix();
	{
		rotationCoord orbit = this->getRotationPlanet()->getOrbitRotationCoord();
		coord distance = this->getRotationPlanet()->getPathToOrbitCenter();

		glRotated(this->getRotationPlanet()->getInitialInclination(), 0.0, 0.0, 1.0);
		glRotated(orbit.angle, orbit.x, orbit.y, orbit.z);
		glTranslated(distance.x, distance.y, distance.z);

		SphereSpaceObject::draw();
	}
	glPopMatrix();
}