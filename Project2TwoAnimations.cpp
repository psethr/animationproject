// Seth Perts
// Project 2 Two Animations
// CPSC 444

#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glut.h>
#include <gl\GL.h>
#include <cmath>
//#include <math>
using namespace std;

void display();
void NormalKeys(unsigned char key, int x, int y);
void myInit();
void text();
void printString(const char *string, float x, float y);
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, int triangleNum, int red, int green, int blue);
void drawGrid(int negX, int posX, int negY, int posY, int numLinesX, int numLinesY);
void drawStar(float x, float y, float startingSize);
void timerStar(int value);
void timerShootingStar(int value);
void handleReshape(GLsizei width, GLsizei height);

int background, shootingStar;
bool animation = true;
float multiplier = 1.0;
float shootingStarX = 0.0;
float shootingStarY = 0.0;

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Seth Perts Project 2 Two Animations");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	myInit();
	glutReshapeFunc(handleReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(NormalKeys);
	glutTimerFunc(0, timerStar, 0);
	glutTimerFunc(0, timerShootingStar, 0);
	glutMainLoop();

	int t;
	cin >> t;
	return 0;
}

void myInit(void)
{
	srand(time(0));
	background = glGenLists(1);
	glNewList(background, GL_COMPILE);
	glColor3ub(102, 34, 0); // brown earth
	glRectf(-10.0, -5.0, 10.0, -100.0);
	drawFilledCircle(0, -11.5, 8.5, 70, 102, 34, 0);
	
	glColor3ub(255, 0, 0); // center point
	glLineWidth(50);
	glBegin(GL_POINTS);
	glVertex2d(0.0, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(-1.0, -3.0, 0.0);
	glColor3ub(255, 255, 255); // Telesope Legs
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(-1.0, -1.0);
	glVertex2f(0.0, 1.5);
	glVertex2f(1.0, -1.0);
	glVertex2f(0.0, 1.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.3, -.79, 0.0);
	glRotatef(-40, 0.0, 0.0, 1.0);
	glColor3ub(255, 255, 255); // Telescope
	glRectf(-1.0, -1.0, .5, -.7);
	glRectf(-1.25, -1.05, -1.05, -.65);
	glRectf(.5, -.9, .9, -.8);
	glRectf(.8, -.8, .9, -.65);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.2, -1, 0.0);
	drawFilledCircle(0, 0, .5, 30, 255, 208, 157); // person
	glLineWidth(7);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.5, -1.5);
	glVertex2f(1.5, -1.5);
	glVertex2f(0.9, -2.2);
	glVertex2f(0.9, -2.2);
	glVertex2f(1.5, -2.9);
	glVertex2f(0.75, -0.75);
	glVertex2f(0.15, -1.45);
	glVertex2f(0.2, -1.4);
	glVertex2f(-0.5, -1.05);
	glEnd();
	glPopMatrix();
	glEndList();

	shootingStar = glGenLists(1);
	glNewList(shootingStar, GL_COMPILE);
	glPushMatrix();

	glColor3ub(255, 255, 255); // line tails
	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex2f(-1.0, 5.0);
	glVertex2f(-2, 1);
	glVertex2f(-.5, 5);
	glVertex2f(-1.5, .5);
	glVertex2f(0, 5);
	glVertex2f(-1, 0);
	glVertex2f(0, 5);
	glVertex2f(0, -.25);
	glVertex2f(0, 5);
	glVertex2f(1, 0);
	glVertex2f(1.0, 5.0);
	glVertex2f(2, 1);
	glVertex2f(.5, 5);
	glVertex2f(1.5, .5);
	glEnd();

	drawFilledCircle(0.0, 5.0, 1.0, 6, 255, 224, 102); // asteriod body
	glColor3ub(255, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1, 5);
	glVertex2f(1, 5);
	glVertex2f(0, 1.5);
	glColor3ub(255, 169, 77);
	glVertex2f(-.5, 5);
	glVertex2f(.5, 5);
	glVertex2f(0, 2);
	glEnd();

	glPopMatrix();

	glEndList();
}

void display(void)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix(); // drawing background
	glCallList(background);
	text();
	glPopMatrix();
	
	glPushMatrix(); // drawing all stars
	drawStar(-9.0, -4.0, .4);
	drawStar(-6.0, -3.0, .2);
	drawStar(-1.0, -2.0, .15);
	drawStar(0.0, 0.0, .1);
	drawStar(-8.0, 4.0, .4);
	drawStar(-9.0, 8.0, .2);
	drawStar(-7.0, 4.0, .3);
	drawStar(-5.0, 7.0, .15);
	drawStar(-3.0, 9.0, .35);
	drawStar(-6.0, 0.0, .45);
	drawStar(1.0, 5.0, .25);
	drawStar(-2.0, 3.0, .3);
	drawStar(0.0, 3.0, .2);
	drawStar(0.0, 9.75, .2);
	drawStar(2.0, 8.0, .3);
	drawStar(2.0, 0.0, .15);
	drawStar(3.0, 1.5, .25);
	drawStar(4.0, 6.0, .15);
	drawStar(6.0, 1.0, .45);
	drawStar(7.0, .75, .25);
	drawStar(9.0, 9.0, .3);
	drawStar(8.0, 5.0, .3);
	drawStar(3.0, -2.0, .3);
	drawStar(5.0, -4.0, .15);
	drawStar(9.0, -3.0, .35);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0 + shootingStarX, 12 + shootingStarY, 0.0);
	glRotatef(-130, 0.0, 0.0, 1.0);
	glScalef(.3, .3, 1.0);
	glCallList(shootingStar);
	glPopMatrix();

	//drawGrid(-10, 10, -10, 10, 20, 20);
	glutSwapBuffers();
}

void NormalKeys(unsigned char key, int x, int y)
{
	if (key == 's' || key == 'S') // start stop the animation
	{
		if (animation)
		{
			animation = false;
		}
		else
		{
			animation = true;
		}
	}
	else if (key == 27 || key == 'q' || key == 'Q')
	{
		exit(0);
	}
	glutPostRedisplay();
}

void printString(const char *string, float x, float y)
{
	const char *c;
	glRasterPos2f(x, y);
	glLineWidth(5);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
	}
}


void text()
{
	glColor3ub(0, 0, 150);
	printString("Welcome to the Two Animations Project", -9, -7.5);
	printString("By: Seth Perts", -9, -8);
	printString("---------------------", -9, -8.5);
	printString("Press 's' or 'S' to start/ stop the animation", -9, -9);
	printString("Press 'q' or 'esc' to exit the project", -9, -9.5);
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, int triangleNum, int red, int green, int blue)
{
	int i;
	int triangleAmount = triangleNum; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;
	glColor3ub(red, green, blue);
	//this code beneath was from github https://gist.github.com/linusthe3rd/803118
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	//this code above was from github https://gist.github.com/linusthe3rd/803118
}

void drawGrid(int negX, int posX, int negY, int posY, int numLinesX, int numLinesY) // created function to draw a grid on any view
{
	int numX = (negX*-1) + posX;
	int numY = (negY*-1) + posY;
	float spaceX = numX / numLinesX;
	float spaceY = numX / numLinesY;
	
	for (int i = 0; i < numLinesX; i++)
	{
		glColor3ub(255, 255, 255);
		if (numLinesX / 2 == i)
		{
			glLineWidth(3);
			glBegin(GL_LINES);
			glVertex2f(negX + (spaceX*i), negY);
			glVertex2f(negX + (spaceX*i), posY);
			glEnd();
			continue;
		}
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2f(negX + (spaceX*i), negY);
		glVertex2f(negX + (spaceX*i), posY);
		glEnd();
	}
	for (int i = 0; i < numLinesY; i++)
	{
		glColor3ub(255, 255, 255);
		if (numLinesY / 2 == i)
		{
			glLineWidth(3);
			glBegin(GL_LINES);
			glVertex2f(negX, negY + (spaceY*i));
			glVertex2f(posX, negY + (spaceY*i));
			glEnd();
			continue;
		}
		glLineWidth(.1);
		glBegin(GL_LINES);
		glVertex2f(negX, negY + (spaceY*i));
		glVertex2f(posX, negY + (spaceY*i));
		glEnd();
	}
}

void drawStar(float x, float y, float startingSize) // function to create a star with lines
{
	float rad = (startingSize*multiplier) / 2.0;
	glColor3ub(255, 255, 255);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(x, y - rad);
	glVertex2f(x, y + rad);
	glVertex2f(x - rad, y);
	glVertex2f(x + rad, y);
	glVertex2f(x - (rad*.75), y + (rad*.75));
	glVertex2f(x + (rad*.75), y - (rad*.75));
	glVertex2f(x - (rad*.75), y - (rad*.75));
	glVertex2f(x + (rad*.75), y + (rad*.75));
	glVertex2f(x - (rad), y - ((rad / 2)));
	glVertex2f(x + (rad), y + ((rad / 2)));
	glVertex2f(x + (rad), y - ((rad / 2)));
	glVertex2f(x - (rad), y + ((rad / 2)));
	glVertex2f(x - (rad / 2), y - ((rad)));
	glVertex2f(x + (rad / 2), y + ((rad)));
	glVertex2f(x + (rad / 2), y - ((rad)));
	glVertex2f(x - (rad / 2), y + ((rad)));
	glEnd();
}

void timerStar(int value) // func for the star animation
{
	if (animation)
	{
		if (multiplier == 1.0)
		{
			multiplier = 1.2;
		}
		else
		{
			multiplier = 1.0;
		}
		glutPostRedisplay();
	}

	glutTimerFunc(400, timerStar, 0);
}

void timerShootingStar(int value) // func for the shooting star animation
{
	if (animation)
	{
		if (shootingStarX > 25)
		{
			shootingStarX = 0;
			shootingStarY = 0;
			glutPostRedisplay();
		}
		shootingStarX += .1;
		shootingStarY -= .1;
		glutPostRedisplay();
	}

	glutTimerFunc(25, timerShootingStar, 0);
}

void handleReshape(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}
	GLfloat asp = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height)
	{
		gluOrtho2D(-10 * asp, 10.0 * asp, -10, 10.0);
	}
	else
	{
		gluOrtho2D(-10, 10.0, -10 / asp, 10.0 / asp);
	}
}