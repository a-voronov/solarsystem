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

#include "SphereSpaceObject.h"
#include <vector>
#include "camera.h"
#include "Sun.h"

class SolarSystemController
{
private:
	Star *m_sun;

protected:
	double currentEarthRotation;
	double earthDaysTranspired;
	double earthDayIncrement;
	double earthDaysTranspirationLimit;
	std::vector<SphereSpaceObject*> spaceObjects;

	void updateLights(void);

public:
	SolarSystemController(void);
	~SolarSystemController(void);

	void initObjectsTextures(void);
	void display(Camera *camera);
	void timerObjectsMovement(void);

	double getRotationSpeed(void);
	void setRotationSpeed(double speed);
};

