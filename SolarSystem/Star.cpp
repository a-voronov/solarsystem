#include "StdAfx.h"
#include "Star.h"


Star::Star() : SphereSpaceObject() { }
Star::Star(double depthValue) : SphereSpaceObject(depthValue) { }
Star::~Star(void) { }

void Star::initTextures(void)
{
	SphereSpaceObject::initTextures();

	this->particleImage.load(TEXT("Bitmaps/particle.bmp"));
	GLuint imgTexture = this->particleTexture;
	glGenTextures(1, &imgTexture);
}

void Star::draw()
{
	SphereSpaceObject::draw();
	// this->drawShining();
}

void Star::drawShining(SHINING_METHOD shineWith) 
{
	if (shineWith == SHINING_METHOD_PARTICLES)
	{
		glEnable(GL_BLEND);
		{
			glDepthMask(GL_FALSE);
			glBlendFunc(GL_SRC_COLOR, GL_ONE);

			this->drawAllParticles();

			glDepthMask(GL_TRUE);
		}
		glDisable(GL_BLEND);
	}
	else if (shineWith == SHINING_METHOD_SHADERS)
	{
		
	}
}

void Star::drawAllParticles()
{
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, 
		this->particleImage.getWidth(), this->particleImage.getHeight(), 0, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, this->particleImage.getBits()
	);
	glBindTexture(GL_TEXTURE_2D, particleTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	particles.updateAll();
	for(int i = 0; i < particles.getNumberOfParticles(); i++)
	{
		drawParticle(particles.getNextParticle());
	}
}

void Star::drawParticle(Particle currParticle)
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
