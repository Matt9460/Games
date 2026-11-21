#ifndef SNAKE_H
#define SNAKE_H

const int width = 20;
const int height = 20;
extern bool gameOver;
extern int x, y, fruitX, fruitY, score;
extern int tailX[100], tailY[100];
extern int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
extern eDirection dir;

void Setup();
void Draw();
void Input();
void Logic();

#endif 