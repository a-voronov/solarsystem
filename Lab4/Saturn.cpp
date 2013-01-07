#include "StdAfx.h"
#include "Saturn.h"
#include "glut.h"


Saturn::Saturn(void) : Planet() { }

Saturn::Saturn(double depthValue) : Planet(depthValue) { }

Saturn::~Saturn(void) { }

double Saturn::getRadius()
{
	return 0.5;
}

coord Saturn::getPathToOrbitCenter()
{
	return coord(7.2, 0.0, 0.0);
}

double Saturn::getOrbitPeriod()
{
	return 10752.9;
}

double Saturn::getSpinPeriod()
{
	return 0.426;
}

LPCWSTR Saturn::getImageName()
{
	return TEXT("Bitmaps/saturnmap.bmp");
}

rotationCoord Saturn::getSpinRotationCoord()
{
	return rotationCoord(this->getSpinRotationAngle(), 0.0, 1.0, 0.0);
}

rotationCoord Saturn::getOrbitRotationCoord()
{
	return rotationCoord(this->getOrbitRotationAngle(), 0.0, 1.0, 0.0);
}

double Saturn::getInitialInclination()
{
	return 2.0;
}

double Saturn::getAxialTiltAngle()
{
	return 26.73;
}

void Saturn::initTextures(void)
{
	Planet::initTextures();

	this->ringImage.load(TEXT("Bitmaps/saturnringmap.bmp"));
	GLuint imgTexture = this->getTexture();
	glGenTextures(1, &imgTexture);
}

void Saturn::draw()
{
	Planet::draw();
	this->drawRing();
}

void Saturn::drawRing()
{
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	gluQuadricDrawStyle(quadro, GLU_FILL);
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
				this->ringImage.getWidth(), this->ringImage.getHeight(), 0, 
				GL_BGR_EXT, GL_UNSIGNED_BYTE, this->ringImage.getBits()
			);

			glRotated(this->getInitialInclination(), 0.0, 0.0, 1.0);
			glRotated(this->getOrbitRotationCoord().angle, 0.0, 1.0, 0.0);
			glTranslated(this->getPathToOrbitCenter().x, 0.0, 0.0 );

			rotationCoord spin = this->getSpinRotationCoord();
			glRotated(spin.angle, spin.x, spin.y, spin.z);

			glRotated(this->sphereDrawnAngle, 1.0, 0.0, 0.0 );
			glScaled(1.0, 1.0, 0.0000000001);
			
			glBindTexture(GL_TEXTURE_2D, this->getTexture());

			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

			glutSolidTorus(this->getRadius() * 0.5, this->getRadius() * 2, 4, 400);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
