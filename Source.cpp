#include <GL\freeglut.h>
#include "Life.h"

#define DELAY 100
#define COUNT_COLUMNS 100
#define COUNT_ROWS 70
#define PIXEL_SIZE_PARTICLE 10

Life game(COUNT_COLUMNS, COUNT_ROWS);
bool play = false;
bool leftKeyPressed = false;
bool rightKeyPressed = false;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for (int x = 1; x < game.size_width; x++)
	{
		glVertex2f(x * PIXEL_SIZE_PARTICLE, 0);
		glVertex2f(x * PIXEL_SIZE_PARTICLE, COUNT_ROWS * PIXEL_SIZE_PARTICLE);
	}
	for (int y = 1; y < game.size_height; y++)
	{
		glVertex2f(0, y * PIXEL_SIZE_PARTICLE);
		glVertex2f(COUNT_COLUMNS * PIXEL_SIZE_PARTICLE, y * PIXEL_SIZE_PARTICLE);
	}
	glEnd();

	glColor3f(0, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	for (int x = 0; x < game.size_width; x++)
		for (int y = 0; y < game.size_height; y++)
		{
			if (game.getElem(x, y))
			{
				glVertex2f(x*PIXEL_SIZE_PARTICLE, y*PIXEL_SIZE_PARTICLE);
				glVertex2f(x*PIXEL_SIZE_PARTICLE, (y + 1)*PIXEL_SIZE_PARTICLE - 1);
				glVertex2f((x + 1)*PIXEL_SIZE_PARTICLE - 1, (y + 1)*PIXEL_SIZE_PARTICLE - 1);
				glVertex2f((x + 1)*PIXEL_SIZE_PARTICLE - 1, y*PIXEL_SIZE_PARTICLE);
			}
		}
	glEnd();

	glutSwapBuffers();
}

void timer(int t)
{
	if (play)
		game.step();
	glutPostRedisplay();
	glutTimerFunc(DELAY, timer, 0);
}

void keyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_SHIFT_L)
		play = !play;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT && state == GLUT_DOWN)
	{
		leftKeyPressed = true;
		game.setElem(x / PIXEL_SIZE_PARTICLE, y / PIXEL_SIZE_PARTICLE, true);
	}
	else if (button == GLUT_LEFT && state == GLUT_UP)
		leftKeyPressed = false;
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		rightKeyPressed = true;
		game.setElem(x / PIXEL_SIZE_PARTICLE, y / PIXEL_SIZE_PARTICLE, false);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		rightKeyPressed = false;

}

void motion(int x, int y)
{
	if (x < 0 || x > COUNT_COLUMNS*PIXEL_SIZE_PARTICLE - 1 || y < 0 || y > COUNT_ROWS*PIXEL_SIZE_PARTICLE - 1)
		return;
	if (leftKeyPressed)
		game.setElem(x / PIXEL_SIZE_PARTICLE, y / PIXEL_SIZE_PARTICLE, true);
	else if (rightKeyPressed)
		game.setElem(x / PIXEL_SIZE_PARTICLE, y / PIXEL_SIZE_PARTICLE, false);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(COUNT_COLUMNS*PIXEL_SIZE_PARTICLE - 1, COUNT_ROWS*PIXEL_SIZE_PARTICLE - 1);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Conway's Game of Life");

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, COUNT_COLUMNS*PIXEL_SIZE_PARTICLE - 1, COUNT_ROWS*PIXEL_SIZE_PARTICLE - 1, 0, -1, 1);
	glutDisplayFunc(display);
	glutTimerFunc(DELAY, timer, 0);
	glutSpecialFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
}