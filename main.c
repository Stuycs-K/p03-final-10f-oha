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

  char * buff = malloc(statbuff->st_size + 1);
  int buffsize = read(openfile, buff, statbuff->st_size);
  buff[buffsize] = '\0';
  if (buffsize < 0){
    err();
  }

  signal(SIGQUIT, sighandler);

  char ** lines = malloc(sizeof(char*));
  char *curr = malloc(strlen(buff) + 1);
  strcpy(curr, buff);
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

  char * newbuff = malloc(strlen(buff) + 1);
  int newbuffsize = strlen(buff);
  strcpy(newbuff, buff);

  
  initscr();
  raw();
  noecho();
  start(buff, statbuff->st_size);
  keypad(stdscr, TRUE);
  while(1){
    int ch = getch();
    if(ch == 28){
      quit(buff, buffsize, openfile, filename);
    }else if (ch == 19){
      buff = realloc(buff, newbuffsize);
      buffsize = newbuffsize;
      strcpy(buff, newbuff);
    }
    int x = 0;
    int y = 0;
    getyx(stdscr, y, x);
    int maxx = 0;
    int maxy = 0;
    getmaxyx(stdscr, maxx, maxy);
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ' || ch == '\t'){
      lines[y] = insert(lines[y], x, ch);
      newbuff = getnewbuff(lines, size, newbuffsize);
      newbuffsize++;
      start(newbuff, newbuffsize);
      move(y, x + 1);
    }else if (ch == KEY_BACKSPACE){
      lines[y] = deletech(lines[y], x - 1);
      newbuff = getnewbuff(lines, size, newbuffsize);
      newbuffsize--;
      start(newbuff, newbuffsize);
      move(y, x - 1);
    }
    movecursor(x,y,lines,size,ch);
  }
  endwin();
}
