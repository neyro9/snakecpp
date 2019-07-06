/* screen.cpp */
#include "screen.h"
#include "cpoint.h"

#define LINE_MAX 255

static CPoint TopLeft;/*dzieki static nie beda usuwane wraz z zakonczeniem funckji*/
static CPoint BottomRight;
static int cury, curx;

void init_screen()
{
  initscr();/*causes the first refresh operation to clear the screen. If err initscr() writes error message to standard err and exits.*/
  cbreak();/*The cbreak() function sets the input mode for the current terminal to cbreak mode and overrides a call to raw(). */
  noecho();/*control whether characters typed by the user are echoed by getch as they are typed. */
  timeout(20);
  nonl();/*control whether the underlying display device translates the return key into newline on inpu*/
  leaveok(stdscr,TRUE);/*allows the cursor to be left wherever the update happens to leave it. It is useful where the cursor is not used*/
  intrflush(stdscr, FALSE);/*prevents the flush*/
  keypad(stdscr, TRUE);/*user can press a function key (such as an arrow key) */
  curs_set(0);/*invisible cursor*/
}

void done_screen()
{/*restores the terminal after Curses activity by at least restoring the saved shell terminal mode, flushing any output to the terminal and moving the cursor to the first column of the last line of the screen.*/
  endwin(); /*Refreshing a window resumes program mode. The application must call */
}/*endwin() for each terminal being used before exiting.*/

void update_screen()
{
  getscreenanchor(TopLeft.y, TopLeft.x);
  getscreensize(BottomRight.y, BottomRight.x);
  BottomRight += TopLeft;
}

int ngetch()
{
  return wgetch(stdscr);
}

void getscreenanchor(int &y, int &x)
{
  getbegyx(stdscr, y, x); /* przechowuje bezwzględne współrzędne ekranu określonego okna w y i x*/
}

void getscreensize(int &y, int &x)
{
  getmaxyx(stdscr, y, x);/*przechowuje liczbę wierszy określonego okna w y i liczbę kolumn w x.*/
}

int gotoyx(int y, int x)
{
  cury=y;
  curx=x;
  return (cury >= TopLeft.y && cury < BottomRight.y && curx >= TopLeft.x && curx < BottomRight.x);
}

void getcursor(int& y, int& x)
{
  y = cury;
  x = curx;
}

void printc(char c)
{
  if(c != '\n' && c != '\r')
  {
    if(cury >= TopLeft.y && cury < BottomRight.y && curx >= TopLeft.x && curx < BottomRight.x)
    {
      wmove(stdscr, cury, curx);
      addch(c);
    }
    curx++;
  }
}

int printl(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  char dest[LINE_MAX];
  vsnprintf(dest, LINE_MAX, fmt, ap);

  int i = 0;
  while(dest[i])
    printc(dest[i++]);

  va_end(ap);
  return !ERR;
}
