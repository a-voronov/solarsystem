#include "StdAfx.h"
#include "SphereSpaceObject.h"

const double SphereSpaceObject::sphereDrawnAngle = -90.0;

//==================================================================================
// Getters & Setters initialization
//==================================================================================

double SphereSpaceObject::getDepthValue(void)
{
	return this->depthValue;
}

void SphereSpaceObject::setDepthValue(double depth)
{
	this->depthValue = depth;
}

double SphereSpaceObject::getSpinRotationAngle(void)
{
	return this->spinRotationAngle;
}

void SphereSpaceObject::setSpinRotationAngle(double angle)
{
	this->spinRotationAngle = angle;
}
	
double SphereSpaceObject::getOrbitRotationAngle(void)
{
	return this->orbitRotationAngle;
}

void SphereSpaceObject::setOrbitRotationAngle(double angle)
{
	this->orbitRotationAngle = angle;
}

//==================================================================================
// Instance methods initialization
//==================================================================================

void SphereSpaceObject::initTextures(void)
{
	this->image.load(this->getImageName());
	GLuint imgTexture = this->texture;
	glGenTextures(1, &imgTexture);
}

void SphereSpaceObject::draw(GLUquadricObj *quadObj)
{
	// glMatrixMode (GL_MODELVIEW);

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(
			GL_TEXTURE_2D, 0, 3, 
			this->image.getWidth(), this->image.getHeight(), 0, 
			GL_BGR_EXT, GL_UNSIGNED_BYTE, this->image.getBits()
		);

		this->orbitalRotation();
		this->spinRotation();
		this->initialRotation();
		
		glDepthFunc(this->getDepthValue());
		gluSphere(quadObj, this->getRadius(), this->getSphereSlices(), this->getSphereStacks());
	}
	glPopMatrix();
}

void SphereSpaceObject::orbitalRotation(void)
{
	if (this->getOrbitPeriod() != 0.0) 
	{
		rotationCoord orbit = this->getOrbitRotationCoord();
		coord distance = this->getDistanceToOrbitCenter();

		glRotated(orbit.angle, orbit.x, orbit.y, orbit.z);
		glTranslated(distance.x, distance.y, distance.z);
	}
}

void SphereSpaceObject::spinRotation(void)
{
	if (this->getSpinPeriod() != 0.0) 
	{
		rotationCoord spin = this->getSpinRotationCoord();
		glRotated(spin.angle, spin.x, spin.y, spin.z);
	}
}

void SphereSpaceObject::initialRotation(void)
{
	rotationCoord init = this->getInitRotationCoord();
	if (init.angle != 0.0) 
	{
		glRotated(init.angle, init.x, init.y, init.z);
	}
}

//==================================================================================
// Virtual methods initialization
//==================================================================================

SphereSpaceObject::~SphereSpaceObject(void) { /* pure virtual destructor */ }

rotationCoord SphereSpaceObject::getInitRotationCoord()
{
	return rotationCoord(0.0 + this->sphereDrawnAngle, 1.0, 0.0, 0.0);
}

double SphereSpaceObject::getSphereSlices(void)
{
	return 20.0;
}

double SphereSpaceObject::getSphereStacks(void)
{
	return 16.0;
}
