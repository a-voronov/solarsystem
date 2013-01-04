#include "StdAfx.h"
#include "SolarSystemController.h"
#include "Sun.h"
#include "Earth.h"

#define windowOrigin screenWidth / 2 - windowWidth / 2, 100

static const int screenWidth = 1366;
static const int screenHeight = 768;
static const int windowWidth = 800;
static const int windowHeight = 200;


SolarSystemController::SolarSystemController(void) 
{ 
	SphereSpaceObject *sun = new Sun();
	SphereSpaceObject *earth = new Earth();

	this->spaceObjects.push_back(sun);
	this->spaceObjects.push_back(earth);
}

SolarSystemController::~SolarSystemController(void) { /* destructor body */ }

void SolarSystemController::reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	initOnReshape();
}

void SolarSystemController::noReshape(GLsizei w, GLsizei h)
{
	glViewport ((w - screenHeight) / 2, (h - screenHeight) / 2, screenHeight, screenHeight);
	initOnReshape();
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

	GLUquadricObj *quadObj;
	quadObj = gluNewQuadric();
	gluQuadricTexture(quadObj, GL_TRUE);
	gluQuadricDrawStyle(quadObj, GLU_FILL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 5.0, 
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0
	);
	
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->spaceObjects[index]->draw(quadObj);
	}

	gluDeleteQuadric(quadObj);

	glFlush();
	glutSwapBuffers();
}

void SolarSystemController::timerObjectsMovement(int value)
{
	// year = (year + 1) % 360;
	// day = (day + 1) % 360;
}

void SolarSystemController::initOnReshape(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// TODO: gona be about ~10000.0 range
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
