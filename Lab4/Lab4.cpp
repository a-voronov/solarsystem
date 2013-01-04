#include "stdafx.h"
#include "SolarSystemController.h"
#include <GL/gl.h>

#define windowOrigin screenWidth / 2 - windowWidth / 2, 100

const int screenWidth = 1366;
const int screenHeight = 768;
const int windowWidth = 800;
const int windowHeight = 200;

SolarSystemController *solarSystem;

void reshape(GLsizei w, GLsizei h);
void noReshape(GLsizei w, GLsizei h);
void display(void);
void timer(int);

int main(int argc, char **argv) 
{
	FreeConsole();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowPosition(windowOrigin);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Solar system");

	solarSystem = new SolarSystemController();
	solarSystem->initObjectsTextures();

	glutReshapeFunc(noReshape);
	glutDisplayFunc(display);
	glutTimerFunc(10, timer, 0);
	glutMainLoop();

	delete solarSystem;

	return 0;
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	solarSystem->initOnReshape();
}

void noReshape(GLsizei w, GLsizei h)
{
	glViewport ((w - screenHeight) / 2, (h - screenHeight) / 2, screenHeight, screenHeight);
	solarSystem->initOnReshape();
}

void display(void)
{
	solarSystem->display();
}

void timer(int)
{   
	solarSystem->timerObjectsMovement();
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}
