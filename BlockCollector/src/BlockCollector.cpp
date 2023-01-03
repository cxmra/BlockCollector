/*
 * snake.cpp
 * Created on: Nov 29, 2022
 * Author: Cameron Anderson
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include "game.h"
#include <stdlib.h>
#include "pixmap/RGBpixmap.h"
#include <windows.h>  // for playing sound
#include <mmsystem.h> //

extern short direction;
bool gameOver = false;
int score = 0, FPS = 15;
GLint winWidth = 700, winHeight = 700;
RGBpixmap pix[2];      /* pixmaps for 6 textures */
int index = 0;

void keyboardFcn(unsigned char key, int, int) {
	switch (key) {
			break;
		case 'a':
			direction = LEFT;
			break;
		case 'd':
			direction = RIGHT;
			break;
	}
}

void timer(int a) {
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawPreston();
	drawFood();
	glutSwapBuffers();
	if (gameOver) {
		char strscore[10];
		itoa(score, strscore, 10);
		char text[50] = "Your Score: ";
		strcat(text, strscore);
		MessageBox(NULL, text, "GAME OVER", 0);
		exit(0);
	}
}

void winReshapeFcn(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COLUMNS, ROWS);
	PlaySound((LPCSTR) "music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	pix[0].readBMPFile("texture/space.bmp");
	pix[0].setTexture(1);

	pix[1].readBMPFile("texture/redtexture.bmp");
	pix[1].setTexture(2);


}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Block Collector - Cam Anderson");
	glutDisplayFunc(display);
	glutReshapeFunc(winReshapeFcn);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboardFcn);
	init();
	glutMainLoop();
	return 0;
}
