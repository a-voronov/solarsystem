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
	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->spaceObjects[index]->initTextures();
	}

	image.load(TEXT("Bitmaps/particle.bmp"));
	GLuint imgTexture = texture;
	glGenTextures(1, &imgTexture);
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

	for (unsigned int index = 0; index < this->spaceObjects.size(); index++)
	{
		this->updateLights();
		this->spaceObjects[index]->draw();
	}

	glEnable(GL_BLEND);
	{
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_COLOR,GL_ONE);

		drawAllParticles();

		glDepthMask(GL_TRUE);
	}
	glDisable(GL_BLEND);

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

void SolarSystemController::drawAllParticles()
{
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, 
		image.getWidth(), image.getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, image.getBits()
	);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	particles.updateAll();
	for(int i = 0; i < particles.getNumberOfParticles(); i++)
	{
		drawParticle(particles.getNextParticle());
	}
}

void SolarSystemController::drawParticle(Particle currParticle)
{
	glPushMatrix();
	{
		glRotatef(currParticle.azimuthRoation, 0, 1, 0);
		glRotatef(currParticle.zenithRotation, 0, 0, 1);

		glPushMatrix();
		{	
			glTranslatef(1.2 + currParticle.surfaceTranslationFactor, 0, 0);
			glScalef(0.5, 0.5, 1.0);

			glBegin(GL_TRIANGLE_STRIP);
			{
				glTexCoord2d(1,1); 
					glVertex3f(0.5f, 0.5f, 0.0f); // Top Right
				glTexCoord2d(0,1);
					glVertex3f(-0.5f, 0.5f, 0.0f); // Top Left
				glTexCoord2d(1,0); 
					glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Right
				glTexCoord2d(0,0); 
					glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Left
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			{
				glTexCoord2d(1,1); 
					glVertex3f(-0.5f, 0.5f, 0.0f); // Top Right
				glTexCoord2d(0,1);
					glVertex3f(0.5f, 0.5f, 0.0f); // Top Left
				glTexCoord2d(1,0); 
					glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Right
				glTexCoord2d(0,0); 
					glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Left
			}
			glEnd();
		}
		glPopMatrix();

		glTranslatef(1.0 + currParticle.surfaceTranslationFactor, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.5, 1.0);

		// Logo Facing Earth
		glBegin(GL_TRIANGLE_STRIP);
		{
			glTexCoord2d(1,1); 
				glVertex3f(0.5f, 0.5f, 0.0f); // Top Right
			glTexCoord2d(0,1);
				glVertex3f(-0.5f, 0.5f, 0.0f); // Top Left
			glTexCoord2d(1,0); 
				glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Right
			glTexCoord2d(0,0); 
				glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Left
		}
		glEnd();

		// Logo Facing Away From Earth
		glBegin(GL_TRIANGLE_STRIP);
		{
			glTexCoord2d(1,1); 
				glVertex3f(-0.5f, 0.5f, 0.0f); // Top Right
			glTexCoord2d(0,1);
				glVertex3f(0.5f, 0.5f, 0.0f); // Top Left
			glTexCoord2d(1,0); 
				glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Right
			glTexCoord2d(0,0); 
				glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Left
		}
		glEnd();
	}
	glPopMatrix();
}
