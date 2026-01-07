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
  int readfile = read(openfile, buff, sizeof(buff));
  if (readfile < 0){
    err();
  }
  initscr();
  printw("%s", buff);
  refresh();
  getch();
  endwin();
}
