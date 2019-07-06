#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <time.h>
#include "cpoint.h"
#include "winsys.h"
#include <vector>
#include "screen.h"
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
class CSnake:public CFramedWindow
{
  vector <CPoint> segments;
  bool help;
  bool pause = true;
  bool gameover;
  char direction;
  CPoint food;
  int score;
  int counter;
  bool running;
public:
  CSnake(CRect r, char _c = ' ');
  void paint();
  bool handleEvent(int c);
  void putfood(); 
  void moveSnake();
  int collision();
  void printmenu();
  void reset();
  void snakeGrow();
  //void eat();

};

#endif
