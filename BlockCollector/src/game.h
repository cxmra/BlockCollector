/*
 * game.h
 * Created on: Nov 29, 2022
 * Author: Cameron Anderson
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#define STOP 0
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define MAX 60
#define COLUMNS 40
#define ROWS 40

void initGrid(int x, int y);
void drawGrid();
void drawSquare(int x, int y);
void drawPreston();
void drawFood();
void randomFood(int&);
void randomColor(int&);
void drawText();

#endif /* SRC_GAME_H_ */
