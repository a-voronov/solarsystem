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
#include "glut.h"
#include <GL/gl.h>

#include "SphereSpaceObject.h"

class SolarSystemController
{
public:
	SolarSystemController(void);
	~SolarSystemController(void);

	void reshape(GLsizei w, GLsizei h);
	void noReshape(GLsizei w, GLsizei h);
	void initObjectsTextures(void);
	void display(void);
	void timerObjectsMovement(int);

protected:
	std::vector<SphereSpaceObject*> spaceObjects;

	void initOnReshape(void);
};

