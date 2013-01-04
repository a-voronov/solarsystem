#pragma once

#include "bitmap.h"
#include "glut.h"
#include <GL/gl.h>
#include "coords.h"


class SphereSpaceObject
{
private:
	double spinRotationAngle;
	double orbitRotationAngle;
	double depthValue;
	BitmapBits image;
	GLuint texture;

	void orbitalRotation(void);
	void spinRotation(void);
	void initialRotation(void);

protected:
	static const double sphereDrawnAngle;

	virtual LPCWSTR			getImageName()				= 0;
	virtual double			getRadius()					= 0; // AU * 10^3
	virtual double			getSpinPeriod()				= 0; // Earth days
	virtual double			getOrbitPeriod()			= 0; // Earth days
	virtual coord			getDistanceToOrbitCenter()	= 0; // AU * 10^3
	virtual rotationCoord	getSpinRotationCoord()		= 0;
	virtual rotationCoord	getOrbitRotationCoord()		= 0;

	virtual rotationCoord	getInitRotationCoord();
	virtual double			getSphereSlices();
	virtual double			getSphereStacks();

public:
	virtual ~SphereSpaceObject(void) = 0;

	BitmapBits getImage(void);
	GLuint getTexture(void);

	double getDepthValue(void);
	void setDepthValue(double depth);

	double getSpinRotationAngle(void);
	void setSpinRotationAngle(double angle);
	
	double getOrbitRotationAngle(void);
	void setOrbitRotationAngle(double angle);

	void initTextures(void);
	void draw(GLUquadricObj *);

	// SphereSpaceObject can have:
	// - surface reflection material
};
