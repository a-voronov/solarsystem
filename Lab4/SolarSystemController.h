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


class SolarSystemController
{
protected:
	double currentEarthRotation;
	double earthDaysTranspired;
	double earthDayIncrement;
	double earthDaysTranspirationLimit;

public:
	SolarSystemController(void);
	~SolarSystemController(void);

	void initObjectsTextures(void);
	void display(Camera *camera);
	void timerObjectsMovement(void);

protected:
	std::vector<SphereSpaceObject*> spaceObjects;
};

