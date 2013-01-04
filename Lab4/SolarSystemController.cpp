#include "StdAfx.h"
#include "SolarSystemController.h"
#include "Sun.h"
#include "Earth.h"

int year = 0;
int day = 0;

SolarSystemController::SolarSystemController(void) 
{
	this->quadObj = gluNewQuadric();

	SphereSpaceObject *sun = new Sun();
	sun->setDepthValue(3.0);
	SphereSpaceObject *earth = new Earth();
	earth->setDepthValue(1.0);

	this->spaceObjects.push_back(sun);
	this->spaceObjects.push_back(earth);
}

SolarSystemController::~SolarSystemController(void) 
{
	gluDeleteQuadric(this->quadObj);
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
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 1, 1);

	gluQuadricTexture(this->quadObj, GL_TRUE);
	gluQuadricDrawStyle(this->quadObj, GLU_FILL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();
	// TODO: gona be about ~10000.0 range
	gluLookAt(
		0.0, 3.0, 1.0, 
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0
	);
	
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->spaceObjects[index]->draw(this->quadObj);
	}

	//glFlush();
	glutSwapBuffers();
}

void SolarSystemController::timerObjectsMovement(void)
{
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		year = (int)(this->spaceObjects[index]->getOrbitRotationAngle() + 1) % 36000;
		day = (int)(this->spaceObjects[index]->getSpinRotationAngle() + 1) % 36000;

		this->spaceObjects[index]->setOrbitRotationAngle(year);
		this->spaceObjects[index]->setSpinRotationAngle(day);
	}
}

void SolarSystemController::initOnReshape(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// TODO: gona be about ~10000.0 range
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
