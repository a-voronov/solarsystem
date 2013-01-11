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

#define SKYFRONT 0
#define SKYBACK  1
#define SKYLEFT  2
#define SKYRIGHT 3
#define SKYUP    4
#define SKYDOWN  5

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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	coord center = this->m_sun->getPathToOrbitCenter();

	float posLight0[4] = {center.x, center.y, center.z, 1.0};
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
	this->initSkyBoxTextures();

	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->spaceObjects[index]->initTextures();
	}
}

void SolarSystemController::initSkyBoxTextures()
{
	this->skyBoxImages[SKYUP].load(TEXT("Bitmaps/Skybox/skybox_top.bmp"));
	GLuint imgTexture1 = skyboxTextures[SKYUP];
	glGenTextures(1, &imgTexture1);

	this->skyBoxImages[SKYDOWN].load(TEXT("Bitmaps/Skybox/skybox_bottom.bmp"));
	GLuint imgTexture2 = skyboxTextures[SKYDOWN];
	glGenTextures(1, &imgTexture2);

	this->skyBoxImages[SKYLEFT].load(TEXT("Bitmaps/Skybox/skybox_left.bmp"));
	GLuint imgTexture3 = skyboxTextures[SKYLEFT];
	glGenTextures(1, &imgTexture3);

	this->skyBoxImages[SKYRIGHT].load(TEXT("Bitmaps/Skybox/skybox_right.bmp"));
	GLuint imgTexture4 = skyboxTextures[SKYRIGHT];
	glGenTextures(1, &imgTexture4);

	this->skyBoxImages[SKYFRONT].load(TEXT("Bitmaps/Skybox/skybox_front.bmp"));
	GLuint imgTexture5 = skyboxTextures[SKYFRONT];
	glGenTextures(1, &imgTexture5);

	this->skyBoxImages[SKYBACK].load(TEXT("Bitmaps/Skybox/skybox_back.bmp"));
	GLuint imgTexture6 = skyboxTextures[SKYBACK];
	glGenTextures(1, &imgTexture6);
}

void SolarSystemController::display(Camera *camera)
{	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	// glEnable(GL_NORMALIZE);

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

	this->drawSkybox(0, 0, 0, 100, 100, 100);

	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->updateLights();
		this->spaceObjects[index]->draw();
	}

	this->m_sun->drawShining(SHINING_METHOD_SHADERS);

	glutSwapBuffers();
	glFlush();
	glDisable(GL_TEXTURE_2D);
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

void SolarSystemController::drawSkybox(float x, float y, float z, float width, float height, float length)
{
	glEnable(GL_TEXTURE_2D);

	GLfloat specular[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat emission[] = {0.2, 0.2, 0.2, 1.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 1.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->skyBoxImages[SKYFRONT].getWidth(), this->skyBoxImages[SKYFRONT].getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, this->skyBoxImages[SKYFRONT].getBits());

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[SKYFRONT]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->skyBoxImages[SKYBACK].getWidth(), this->skyBoxImages[SKYBACK].getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, this->skyBoxImages[SKYBACK].getBits());

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[SKYBACK]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->skyBoxImages[SKYLEFT].getWidth(), this->skyBoxImages[SKYLEFT].getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, this->skyBoxImages[SKYLEFT].getBits());

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[SKYLEFT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->skyBoxImages[SKYRIGHT].getWidth(), this->skyBoxImages[SKYRIGHT].getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, this->skyBoxImages[SKYRIGHT].getBits());

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[SKYRIGHT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->skyBoxImages[SKYUP].getWidth(), this->skyBoxImages[SKYUP].getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, this->skyBoxImages[SKYUP].getBits());

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[SKYUP]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->skyBoxImages[SKYDOWN].getWidth(), this->skyBoxImages[SKYDOWN].getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, this->skyBoxImages[SKYDOWN].getBits());

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, skyboxTextures[SKYDOWN]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
}
