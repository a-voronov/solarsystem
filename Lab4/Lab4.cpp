#include "stdafx.h"
#include "bitmap.h"
#include "glut.h"
#include <GL/gl.h>

#define windowOrigin screenWidth / 2 - windowWidth / 2, 100

static const int screenWidth = 1366;
static const int screenHeight = 768;
static const int windowWidth = 800;
static const int windowHeight = 200;
static int year = 0;
static int day = 0;

GLuint texture[2];
BitmapBits imgSun, imgEarth, imgMoon;

void reshape(GLsizei w, GLsizei h);
void noReshape(GLsizei w, GLsizei h);
void init(void);
void display(void);
void timer(int);

void drawSun(GLUquadricObj *);
void drawEarth(GLUquadricObj *);
void drawMoon(GLUquadricObj *);


int main(int argc, char **argv) 
{
	FreeConsole();

	imgSun.load(TEXT("sun.bmp"));
	imgEarth.load(TEXT("earth.bmp"));
	imgMoon.load(TEXT("moon.bmp"));
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowPosition(windowOrigin);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Solar system");

	glutReshapeFunc (noReshape);
	glutDisplayFunc(display);
	glutTimerFunc(10, timer, 0);
	glutMainLoop();
	
	return 0;
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	init();
}

// instead of reshaping save square proportions
void noReshape(GLsizei w, GLsizei h) 
{
	glViewport ((w - screenHeight) / 2, (h - screenHeight) / 2, screenHeight, screenHeight);
	init();
}

void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	glMatrixMode (GL_MODELVIEW);
}

void display(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 1, 1);

	GLUquadricObj *quadObj;
	quadObj = gluNewQuadric();
	gluQuadricTexture(quadObj, GL_TRUE);
	gluQuadricDrawStyle(quadObj, GLU_FILL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 5.0, 
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0
	);
	
	drawSun(quadObj);
	drawEarth(quadObj);
	drawMoon(quadObj);

	gluDeleteQuadric(quadObj);

	glFlush();
	glutSwapBuffers();
}

void timer(int)
{   
	year = (year + 1) % 360;
	day = (day + 1) % 360;
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void drawSun(GLUquadricObj *quadObj)
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgSun.getWidth(), imgSun.getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imgSun.getBits());

		// spin rotation
		glRotatef(day, 0.0, 1.0, 0.0);

		// rotate sun to be drawn vertically
		glRotatef(-90, 1.0, 0.0, 0.0);

		glDepthFunc(3);
		gluSphere(quadObj, 1.0, 40, 32);
	}
	glPopMatrix();
}

void drawEarth(GLUquadricObj *quadObj)
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgEarth.getWidth(), imgEarth.getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imgEarth.getBits());

		// rotate around sun
		glRotatef(year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0);

		// spin rotation
		glRotatef(day, 0.0, 1.0, 0.0);

		// rotate to eart's angle
		glRotatef(-68, 1.0, 0.0, 0.0);
		
		glDepthFunc(2);
		gluSphere(quadObj, 0.3, 20, 16);
	}
	glPopMatrix();
}

void drawMoon(GLUquadricObj *quadObj)
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgMoon.getWidth(), imgMoon.getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imgMoon.getBits());

		// rotate around sun
		glRotatef(year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0);

		// rotate around earth
		glRotatef(day, 0.0, 1.0, 0.0);
		glTranslatef(0.6, 0.0, 0.0);

		// spin rotation
		glRotatef(day, 0.0, 1.0, 0.0);

		// rotate moon to be drawn vertically
		glRotatef(-90, 1.0, 0.0, 0.0);
		
		glDepthFunc(1);
		gluSphere(quadObj, 0.1, 10, 8);
	}
	glPopMatrix();
}
