#include "StdAfx.h"
#include "SolarSystemController.h"
#include "glut.h"
#include <GL/gl.h>
#include "Sun.h"
#include "Mercury.h"
#include "Venus.h"
#include "Earth.h"
#include "Mars.h"
#include "Jupiter.h"
#include "Saturn.h"
#include "Uranus.h"
#include "Neptune.h"


SolarSystemController::SolarSystemController(void) 
{
	this->currentEarthRotation = 0.0;
	this->earthDaysTranspired = 0.0;
	this->earthDayIncrement = 0.1;
	this->earthDaysTranspirationLimit;

	SphereSpaceObject *earth = new Earth(99799);
	this->earthDaysTranspirationLimit = earth->getOrbitPeriod();

	this->spaceObjects.push_back(new Sun(100000));
	this->spaceObjects.push_back(new Mercury(99999));
	this->spaceObjects.push_back(new Venus(99899));
	this->spaceObjects.push_back(earth);
	this->spaceObjects.push_back(new Mars(99699));
	this->spaceObjects.push_back(new Jupiter(99599));
	this->spaceObjects.push_back(new Saturn(99499));
	this->spaceObjects.push_back(new Uranus(99399));
	this->spaceObjects.push_back(new Neptune(99299));
}

SolarSystemController::~SolarSystemController(void) 
{
	for (unsigned int index = 0; index < this->spaceObjects.size();)
	{
		delete this->spaceObjects[index];
	}
}

void SolarSystemController::initObjectsTextures(void)
{
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->spaceObjects[index]->initTextures();
	}
}

void SolarSystemController::display(void)
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 1, 1);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);	

	glLoadIdentity();
	gluLookAt(
		0.0, 4.0, 4.0, 
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0
	);
	
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->spaceObjects[index]->draw();
	}

	glutSwapBuffers();
}

void SolarSystemController::timerObjectsMovement(void)
{
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->currentEarthRotation += this->earthDayIncrement;
		this->earthDaysTranspired += this->earthDayIncrement;

		if (this->earthDaysTranspired == this->earthDaysTranspirationLimit)
		{
			this->earthDaysTranspired = 0;
		}

		double orbitPeriod = this->spaceObjects[index]->getOrbitPeriod();
		double spinPeriod = this->spaceObjects[index]->getSpinPeriod();

		this->spaceObjects[index]->setOrbitRotationAngle(360.0 * (this->earthDaysTranspired / orbitPeriod));
		this->spaceObjects[index]->setSpinRotationAngle(360.0 * (this->currentEarthRotation / spinPeriod));
	}
}
