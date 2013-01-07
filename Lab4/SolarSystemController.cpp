#include "StdAfx.h"
#include "SolarSystemController.h"
#include "glut.h"
#include <GL/gl.h>
#include "Sun.h"
#include "Mercury.h"
#include "Venus.h"
#include "Earth.h"
#include "Moon.h"
#include "Mars.h"
#include "Jupiter.h"
#include "Saturn.h"
#include "Uranus.h"
#include "Neptune.h"
#include "Pluto.h"

//const float scale = 10.0;

SolarSystemController::SolarSystemController(void) 
{
	this->currentEarthRotation = 0.0;
	this->earthDaysTranspired = 0.0;
	this->earthDayIncrement = 0.8;

	SphereSpaceObject *earth = new Earth(99799);
	this->earthDaysTranspirationLimit = earth->getOrbitPeriod();

	this->spaceObjects.push_back(new Sun(100000));
	this->spaceObjects.push_back(new Mercury(99999));
	this->spaceObjects.push_back(new Venus(99899));
	this->spaceObjects.push_back(earth);
	this->spaceObjects.push_back(new Moon(99789, (Planet*)earth));
	this->spaceObjects.push_back(new Mars(99699));
	this->spaceObjects.push_back(new Jupiter(99599));
	this->spaceObjects.push_back(new Saturn(99499));
	this->spaceObjects.push_back(new Uranus(99399));
	this->spaceObjects.push_back(new Neptune(99299));
	this->spaceObjects.push_back(new Pluto(99199));
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

void SolarSystemController::display(Camera *camera)
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 1, 1);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);	

	glLoadIdentity();
	gluLookAt(
		camera->m_vPosition.x,	camera->m_vPosition.y,	camera->m_vPosition.z, 
		camera->m_vView.x,		camera->m_vView.y,		camera->m_vView.z, 
		camera->m_vUpVector.x,	camera->m_vUpVector.y,	camera->m_vUpVector.z
	);
	
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->spaceObjects[index]->draw();
	}

	//glEnable(GL_BLEND);
	//glDepthMask(GL_TRUE);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE);

	glutSwapBuffers();
	glFlush();
}

void SolarSystemController::timerObjectsMovement(void)
{
	this->currentEarthRotation += this->earthDayIncrement;
	this->earthDaysTranspired += this->earthDayIncrement;

	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		double orbitPeriod = this->spaceObjects[index]->getOrbitPeriod();
		double spinPeriod = this->spaceObjects[index]->getSpinPeriod();

		this->spaceObjects[index]->setSpinRotationAngle((this->currentEarthRotation / spinPeriod) * 360.0);
		this->spaceObjects[index]->setOrbitRotationAngle((this->earthDaysTranspired / orbitPeriod) * 360.0);	
	}
}

double SolarSystemController::getRotationSpeed(void)
{
	return this->earthDayIncrement;
}

void SolarSystemController::setRotationSpeed(double speed)
{
	if (speed > 100.0)  
	{
		this->earthDayIncrement = 100.0;
		return;
	}
	else if(speed < 0.1)
	{
		this->earthDayIncrement = 0.1;
		return;
	}
	this->earthDayIncrement = speed;
}
