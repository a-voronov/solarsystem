#pragma once

#include "SphereSpaceObject.h"
#include "ParticleSystem.h"

typedef enum SHINING_METHOD
{
	SHINING_METHOD_PARTICLES,
	SHINING_METHOD_SHADERS
} SHINING_METHOD;

class Star : public SphereSpaceObject
{
private:
	BitmapBits particleImage;
	ParticleSystem particles;
	GLuint particleTexture;

protected:
	void drawAllParticles(void);
	void drawParticle(Particle currParticle);

public:
	Star(void);
	Star(double depthValue);
	virtual ~Star(void) = 0;

	void drawShining(SHINING_METHOD shineWith);
	void draw(void);
	void initTextures(void);
};

