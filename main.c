#include "editor.h"
int main(){
  initscr();
  clear();
  mvprintw(3, 5, "Hello, world!");
  refresh();
  getch();
  endwin();
}
