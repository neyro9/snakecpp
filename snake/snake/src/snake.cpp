#include "snake.h"


CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
	segments.push_back(CPoint(5,3));
	segments.push_back(CPoint(4,3));
	segments.push_back(CPoint(3,3));
	running = 0;
	help = 1;
	direction = 'r';
	//food = CPoint(15,5);
	score = 0;
	gameover = 0;
	counter = 0;
	pause = 1;
	putfood();	
}
int CSnake::collision()
{
	for(unsigned i=1;i<segments.size();i++)
	{
		if(segments[i].x==segments[0].x && segments[i].y==segments[0].y)
			return 1;
	}
	return 0;
}
void CSnake::paint()
{
	if(!gameover)
	{	
		gotoyx(geom.topleft.y-1,geom.topleft.x);
		printl("| LEVEL: %d |",score);
	}  	
	CFramedWindow::paint();
	gotoyx(geom.topleft.y+food.y,geom.topleft.x+food.x);		
	printc('O');
	for(unsigned int i=0;i<segments.size();i++)
	{
		gotoyx(geom.topleft.y+segments[i].y,geom.topleft.x+segments[i].x);
		if(i==0)
			printc('*');
		else 
			printc('+');
	}
	if(help)
  		printmenu();
	if(collision())
	{
		running = 0;
		help = 0;
		pause = 0;
		gotoyx(geom.topleft.y+1, geom.topleft.x+1);
    		printl("GameOver, result : %u", score);
		gotoyx(geom.topleft.y+2, geom.topleft.x+1);
		printl("Press r to restart  game");
		gameover = 1;
		counter = 0;
	}
	if(segments[0].x == food.x && segments[0].y == food.y)
	{	
		putfood();
		snakeGrow();
	}
}
void CSnake::printmenu()
{
	    gotoyx(geom.topleft.y+5, geom.topleft.x+6);
	    printl("h - toggle for help information");
	    gotoyx(geom.topleft.y+6, geom.topleft.x+6);
	    printl("p - toggle pause/play mode");
	    gotoyx(geom.topleft.y+7, geom.topleft.x+6);
	    printl("r - restart game");
	    gotoyx(geom.topleft.y+8, geom.topleft.x+6);
	    printl("arrow - move snake (in play mode) or");
	    gotoyx(geom.topleft.y+9, geom.topleft.x+9);
	    printl("move window (in pause mode)");
}	
void CSnake::putfood()
{
	srand(time(NULL));
	while(1){
		int tmpx=rand()%(geom.size.x-2)+1;
		int tmpy=rand()%(geom.size.y-2)+1;
		int size = segments.size();
		for(int i=0;i<size;++i)
		{
			if(segments[i].x==tmpx && segments[i].y==tmpy) putfood();
		}
		food.x = tmpx;
		food.y = tmpy;
		break;
	}
}
void CSnake::snakeGrow()
{
	CPoint last = segments[segments.size()-1];
	segments.push_back(last);
	score++;
}

void CSnake::reset()
{
	score = 0;
	segments.clear();
	segments.push_back(CPoint(5,3));
	segments.push_back(CPoint(4,3));
	segments.push_back(CPoint(3,3));
	running=0;
	help=1;
	direction='r';
	pause = 1;
	gameover=0;
	putfood();
}
void CSnake::moveSnake()
{
	if(running)
  	{
		for(unsigned i=segments.size()-1;i>0;i--)
		{
			segments[i] = segments[i-1];
		}
  		if(direction=='u')
		  	segments[0].y--;
		else if (direction=='d')
			segments[0].y++;
		else if (direction=='r')
			segments[0].x++;
		else if (direction=='l')
			segments[0].x--;
		if(segments[0].x <= 0)
			segments[0].x = geom.size.x -2;
		else if(segments[0].y <= 0)
			segments[0].y = geom.size.y - 2;
		else if(segments[0].x >= geom.size.x-1)
			segments[0].x = 0;
		else if(segments[0].y >= geom.size.y-1)
			segments[0].y = 0; 
	}
}
bool CSnake::handleEvent(int c)
{
	if(c=='r')
	{
		reset();
		return true;
	}
	if(c=='h')
	{
		help = !help;
		pause = true;		
		return true;
	}
	if(help)
	{
		running=0;
		if(CFramedWindow::handleEvent(c))
   			return true;
   	}
    	if(c=='p')
	{    	
		pause = !pause;
		help = false;
		if(!pause)
		{
			//help = false;
			running = 1;
		}
		else running = 0;
   		return true;
	}
    if(!running)
    	if(CFramedWindow::handleEvent(c))
   			return true;
    switch(c)
    {
    	case KEY_UP:
		if(direction!='d')
		{
		      direction='u';
		}
		moveSnake();	
		counter = 0;
    	 return true;
			
	
    	case KEY_DOWN:
    		if(direction!='u')
		{
		      direction='d';
		}
		moveSnake();
		counter = 0;
    	  return true;
    	case KEY_RIGHT:
		if(direction!='l')
		{
		      direction='r';
		}
		moveSnake();
		counter = 0;
    	  return true;
    	case KEY_LEFT:
		if(direction!='r')
		{
		      direction='l';
		}
		moveSnake();
		counter = 0;
    		  return true;
	}
	if(c==ERR)
	{
		counter++;
		if(counter==10-score/3 || score > 29)
		{
			moveSnake();
			counter = 0;
		}
		return true;
	}
	
	return false;
}
