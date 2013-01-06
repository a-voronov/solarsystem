#include "stdafx.h"
#include "SolarSystemController.h"
#include "glut.h"
#include <GL/gl.h>

const int windowWidth = 900;
const int windowHeight = 500;

SolarSystemController *solarSystem;

void reshape(GLsizei w, GLsizei h);
void initOnReshape(double width, double height);
void display(void);
void timer(int);

int main(int argc, char **argv) 
{
	FreeConsole();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	int windowOriginX = glutGet(GLUT_SCREEN_WIDTH) / 2 - windowWidth / 2;
	int windowOriginY = glutGet(GLUT_SCREEN_HEIGHT) / 2 - windowHeight / 2;

	glutInitWindowPosition(windowOriginX, windowOriginY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Solar system");

	solarSystem = new SolarSystemController();
	solarSystem->initObjectsTextures();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutMainLoop();

	delete solarSystem;

	return 0;
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	initOnReshape(w, h);
}

void initOnReshape(double width, double height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double aspectRatio = width / height;

	glFrustum(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	solarSystem->display();
}

void timer(int)
{   
	solarSystem->timerObjectsMovement();
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}
