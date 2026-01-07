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
  printf("%s",buff);
  initscr();
  clear();
  scrollok(stdscr, TRUE);

  int row = 0;
  int col = 0;
  int maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);

  for (int i = 0; i < statbuff->st_size; i++){
    char n = buff[i];

    if(n == '\n'){
      row++;
      col = 0;
    }
    else{
      mvaddch(row, col, n);
      col++;
      if(col >= maxx){
        row++;
        col = 0;
      }
    }

    if(row>=maxy){
      scroll(stdscr);
      row = maxy - 1;
    }
  }
  refresh();
  getch();
  endwin();
}
