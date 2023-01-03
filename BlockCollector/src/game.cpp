/*
 * game.cpp
 * Created on: Nov 29, 2022
 * Author: Cameron Anderson
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include <ctime>
#include "game.h"
#include <stdio.h>
#include <iostream>
#include <string>

int gridX, gridY;
int slength = 4;
bool food = true;
int foodX, foodY = ROWS;
int posX[4] = {22, 21, 20, 19}, posY[4] = {1, 1, 1, 1};
short direction = STOP;
int rColor, choices = 7;

extern bool gameOver;
extern int score;
extern int FPS;

void initGrid(int x, int y) {
	gridX = x;
	gridY = y;
}

void drawGrid() {
	glColor3f(1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,2);
	glBegin(GL_QUADS);
		glTexCoord2i(0, 0); 		glVertex2f(0, 0);
		glTexCoord2i(0, 1);     glVertex2f(0, 1);
		glTexCoord2i(1, 1); glVertex2f(gridX, 1);
		glTexCoord2i(1, 0);     glVertex2f(gridX, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,1);
	glBegin(GL_QUADS);
		glTexCoord2i(0, 0); 		glVertex2f(0, 1);
		glTexCoord2i(0, 1);     glVertex2f(0, gridY);
		glTexCoord2i(1, 1); glVertex2f(gridX, gridY);
		glTexCoord2i(1, 0);     glVertex2f(gridX, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawSquare(int x, int y) {
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x+1, y);
			glVertex2f(x+1, y+1);
			glVertex2f(x, y+1);
		glEnd();
	}
}

void drawPreston() {
	if (direction == RIGHT && posX[0] < (gridX - 1)) {
		posX[0]++;
		posX[1]++;
		posX[2]++;
		posX[3]++;
	} else if (direction == LEFT && posX[3] > 0) {
		posX[0]--;
		posX[1]--;
		posX[2]--;
		posX[3]--;
	}
	direction = STOP;
	for (int i = 0; i < slength; i++) {
		glColor3f(0.0, 0.0, 1.0);
		glRectd(posX[i], posY[i], posX[i]+1, posY[i]+1);
	}

	if ((posX[0] == foodX || posX[1] == foodX || posX[2] == foodX || posX[3] == foodX) && foodY == 1) {
		if (rColor < 4) {
			score++;
			FPS+=2;
			rColor = 0;
			food = true;
		} else if (rColor == 4 || rColor == 5) {
			gameOver = true;
		} else if (rColor > 5) {
			score++;
			FPS--;
			rColor = 0;
			food = true;
		}
	}
}

void drawFood() {
	if (food) {
		randomFood(foodX);
		foodY = ROWS;
		food = false;
	}
	if (rColor == 0) {
		if (FPS == 15) {
			choices = 5;
		} else {
			choices = 7;
		}
		randomColor(rColor);
	}
	if (rColor < 4) {
		glColor3f(1.0, 1.0, 0.0);
	} else if (rColor == 4 || rColor == 5) {
		glColor3f(1.0, 0.0, 0.0);
	} else if (rColor > 5) {
		glColor3f(0.0, 1.0, 0.0);
	}

	glRectd(foodX, foodY, foodX+1, foodY+1);
	if (foodY > 0) {
		foodY--;
	} else if (foodY == 0 && rColor < 4) {
		gameOver = true;
	} else if (foodY == 0) {
		rColor = 0;
		food = true;
	}
}

void randomFood(int &x) {
	int maxX = gridX - 2, min_val = 1;
	srand(time(NULL)); // seed random number (not the same number twice)
	x = (rand() % maxX) + min_val;
}

void randomColor(int &x) {
	x = (rand() % choices) + 1;
}
