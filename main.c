#include "editor.h"
static void sighandler(int signo){
  if(signo == SIGQUIT){
  }
}

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
  signal(SIGQUIT, sighandler);
  char ** lines = malloc(sizeof(char*));
  char *curr = buff;
  char * token = calloc(1, sizeof(buff) + 1);
  int size = 1;
  token = strsep(&curr, "\n");
  while(token != NULL){
    lines = realloc(lines, size * sizeof(char*));
    lines[size - 1] = token;
    token = strsep(&curr, "\n");
    size++;
  }
  lines = realloc(lines, size * sizeof(char*));
  lines[size - 1] = NULL;
  size--;
  initscr();
  raw();
  noecho();
  start(buff, statbuff);
  keypad(stdscr, TRUE);
  while(1){
    if(getch() == 28){
      quit(buff, statbuff);
    }
    int x = 0;
    int y = 0;
    getyx(stdscr, y, x);
    int maxx = 0;
    int maxy = 0;
    getmaxyx(stdscr, maxx, maxy);
    int ch = getch();
    movecursor(x,y,lines,size,ch);

  }
  endwin();
}
