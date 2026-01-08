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
  int size = 2;
  token = strsep(&line, "\n");
  while(token != NULL){
    lines = realloc(lines, size * sizeof(char*));
    lines[size - 1] = token;
    token = strsep(&line, " ");
    size++;
  }
  argary[size - 1] = NULL;
  while((token = strsep(&curr)) != NULL){

  }
  initscr();
  raw();
  noecho();
  start(buff, statbuff);
  keypad(stdscr, TRUE);
  while(1){
    if(getch() == 28){
      clear();
      printw("Are you sure you want to quit (Y/N)");
      refresh();
      while(1){
        int ch = getch();
        if(ch == 'y'){
          endwin();
          exit(0);
        }else if (ch == 'n'){
          start(buff, statbuff);
          break;
        }
      }      
    }
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
