#include "StdAfx.h"
#include "SphereSpaceObject.h"
#include "glut.h"

const double SphereSpaceObject::sphereDrawnAngle = -90.0;

SphereSpaceObject::SphereSpaceObject(void) 
{
	this->setOrbitRotationAngle(0.0);
	this->setSpinRotationAngle(0.0);
}

SphereSpaceObject::SphereSpaceObject(double depthValue)
{
	this->setDepthValue(depthValue);
}

//==================================================================================
// Getters & Setters initialization
//==================================================================================

GLuint SphereSpaceObject::getTexture(void)
{
	return this->texture;
}

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
	GLuint imgTexture = this->getTexture();//this->texture;
	glGenTextures(1, &imgTexture);
}

void SphereSpaceObject::draw(void)
{
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricDrawStyle(quadro, GLU_FILL);
	gluQuadricTexture(quadro, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glPushMatrix();
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
			glBindTexture(GL_TEXTURE_2D, this->getTexture());
			gluSphere(quadro, this->getRadius(), this->getSphereSlices(), this->getSphereStacks());
		}
		glPopMatrix();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

void SphereSpaceObject::orbitalRotation(void)
{
	if (this->getOrbitPeriod() != 0.0) 
	{
		rotationCoord orbit = this->getOrbitRotationCoord();
		coord distance = this->getPathToOrbitCenter();

		glRotated(this->getInitialInclination(), 0.0, 0.0, 1.0);
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
	return rotationCoord(this->sphereDrawnAngle, 1.0, 0.0, 0.0);
}

double SphereSpaceObject::getAxialTiltAngle(void)
{
	return 0.0;
}

double SphereSpaceObject::getSphereSlices(void)
{
	return 40.0;
}

double SphereSpaceObject::getSphereStacks(void)
{
	return 32.0;
}
