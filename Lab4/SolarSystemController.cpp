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

SolarSystemController::SolarSystemController(void) 
{
	this->currentEarthRotation = 0.0;
	this->earthDaysTranspired = 0.0;
	this->earthDayIncrement = 0.8;

	SphereSpaceObject *earth = new Earth(99799);
	this->earthDaysTranspirationLimit = earth->getOrbitPeriod();
	SphereSpaceObject *sun = new Sun(100000);
	this->m_sun = (Star*)sun;

	this->spaceObjects.push_back(sun);
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

void SolarSystemController::updateLights(void)
{
	/*
	// From RedBook
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {128.0};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	*/
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	float posLight0[4] = {0.0, 0.0, 0.0, 1.0};
	float ambLight0[4] = {0.2, 0.2, 0.2, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight0);

	GLfloat specular[] = {0.05, 0.05, 0.0, 1.0};
	GLfloat emission[] = {0.0, 0.0, 0.0, 1.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 0.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glColor3d(1, 1, 1);

	glLoadIdentity();
	gluLookAt(
		camera->m_vPosition.x,	camera->m_vPosition.y,	camera->m_vPosition.z, 
		camera->m_vView.x,		camera->m_vView.y,		camera->m_vView.z, 
		camera->m_vUpVector.x,	camera->m_vUpVector.y,	camera->m_vUpVector.z
	);

	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->updateLights();
		this->spaceObjects[index]->draw();
	}

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
