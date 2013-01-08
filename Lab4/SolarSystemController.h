/***********************************************************************************
 **							Maybe will make it as singleton						  **
 ***********************************************************************************

// (.h)
class Singleton
{
private: 
	static Singleton* _instance;
 
	Singleton() { }
 
public:
	static Singleton* getInstance();
};
 
// (.cpp)
Singleton* Singleton::_instance = 0;
 
Singleton* Singleton::getInstance()
{
	if (!_instance)
	{
		_instance = new Singleton;
	}
	return _instance;
}
************************************************************************************/

#pragma once

#include <vector>
#include "ParticleSystem.h"
#include "SphereSpaceObject.h"
#include "camera.h"
#include "Sun.h"


class SolarSystemController
{
private:
	Star *m_sun;
	ParticleSystem particles;
	GLuint texture;
	BitmapBits image;

protected:
	double currentEarthRotation;
	double earthDaysTranspired;
	double earthDayIncrement;
	double earthDaysTranspirationLimit;
	std::vector<SphereSpaceObject*> spaceObjects;

	void updateLights(void);
	void drawAllParticles(void);
	void drawParticle(Particle currParticle);

public:
	SolarSystemController(void);
	~SolarSystemController(void);

	void initObjectsTextures(void);
	void display(Camera *camera);
	void timerObjectsMovement(void);

	double getRotationSpeed(void);
	void setRotationSpeed(double speed);
};

