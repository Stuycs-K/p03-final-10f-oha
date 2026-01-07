#include "editor.h"
int main(int argc, char *argv[]){
  char * filename = argv[1];
  int openfile = open(filename, O_RDWR, 0666);
  if(openfile < 0){
    err();
  }
  struct stat *statbuff = malloc(sizeof(struct stat));
  stat(filename, statbuff);
  char * buff = malloc(statbuff->st_size);
  int readfile = read(openfile, buff, statbuff->st_size);
  buff[readfile] = '\0';
  if (readfile < 0){
    err();
  }
  initscr();
  start(buff, statbuff);
  keypad(stdscr, TRUE);
  while(1){
    int x = 0;
    int y = 0;
    getyx(stdscr, y, x);
    int maxx = 0;
    int maxy = 0;
    getmaxyx(stdscr, maxx, maxy);
    int ch = getch();
    movecursor(x,y,maxx,maxy,ch);
  }
  endwin();
}
