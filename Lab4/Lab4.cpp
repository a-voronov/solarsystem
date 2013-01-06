#include "stdafx.h"
#include "SolarSystemController.h"
#include "glut.h"
#include <GL/gl.h>
#include "camera.h"

const float movementSpeed = 0.003f;
const float acceleration = 5.0;
const int timerFrequency = 20;

const int windowWidth = 900;
const int windowHeight = 500;

SolarSystemController *solarSystem;
Camera *camera;

void reshape(GLsizei w, GLsizei h);
void initOnReshape(double width, double height);
void display(void);
void keyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void timer(int);

int main(int argc, char **argv) 
{
	FreeConsole();

	camera = new Camera();
	solarSystem = new SolarSystemController();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutGameModeString("1024x768:64@75");
	glutEnterGameMode();
	glutSetCursor(GLUT_CURSOR_NONE);

	solarSystem->initObjectsTextures();
	camera->positionCamera(
		0.0, 4.0, 4.0, 
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0
	);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardPress);
	glutTimerFunc(timerFrequency, timer, 0);
	glutMainLoop();

	delete solarSystem;
	delete camera;

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

	gluPerspective(60.0, aspectRatio, 0.2, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	camera->setViewByMouse();
	solarSystem->display(camera);
}

void keyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	switch(pressedKey)
	{
		case 'w'://VK_UP:
		{
			camera->moveCamera(movementSpeed);
			break;
		}
		case 'W'://VK_UP:
		{
			camera->moveCamera(movementSpeed * acceleration);
			break;
		}
		case 's'://VK_DOWN:
		{
			camera->moveCamera(-movementSpeed);
			break;
		}
		case 'S'://VK_UP:
		{
			camera->moveCamera(-movementSpeed * acceleration);
			break;
		}
		case 'a'://VK_LEFT:
		{
			camera->rotateAroundPoint(camera->m_vView, movementSpeed, 0, 1, 0);
			break;
		}
		case 'A'://VK_LEFT:
		{
			camera->rotateAroundPoint(camera->m_vView, movementSpeed  * acceleration, 0, 1, 0);
			break;
		}
		case 'd'://VK_RIGHT:
		{
			camera->rotateAroundPoint(camera->m_vView, -movementSpeed, 0, 1, 0);
			break;
		}
		case 'D'://VK_RIGHT:
		{
			camera->rotateAroundPoint(camera->m_vView, -movementSpeed * acceleration, 0, 1, 0);
			break;
		}
		case 27:
		{
			if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0) 
			{
				glutLeaveGameMode();
				exit(0);
			}
			break;
		}
	}
}

void timer(int)
{   
	solarSystem->timerObjectsMovement();
	glutPostRedisplay();
	glutTimerFunc(timerFrequency, timer, 0);
}
