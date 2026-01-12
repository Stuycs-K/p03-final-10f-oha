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
  char *curr = malloc(strlen(buff) + 1);
  strcpy(curr, buff);
  printf("%s\n", curr);
  printf("\n");
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

  printf("%s\n",lines[0]);
  printf("\n");


  char * newbuff = malloc(sizeof(buff));
  int newbuffsize = statbuff->st_size;
  strcpy(newbuff, buff);

  printf("%s\n", buff);
  printf("\n");
  printf("%s\n",newbuff);
  printf("\n");
  /*initscr();
  raw();
  noecho();
  start(buff, statbuff->st_size);
  keypad(stdscr, TRUE);
  while(1){
    int ch = getch();
    if(ch == 28){
      quit(newbuff, newbuffsize);
    }
    int x = 0;
    int y = 0;
    getyx(stdscr, y, x);
    int maxx = 0;
    int maxy = 0;
    getmaxyx(stdscr, maxx, maxy);
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
      lines[y] = insert(lines[y], x, ch);
      newbuff == getnewbuff(lines, size);
      newbuffsize++;
      start(newbuff, newbuffsize);
    }
    movecursor(x,y,lines,size,ch);
  }
  endwin();*/
  printf("%s\n", lines[0]);
  printf("\n");
  lines[0] = insert(lines[0], 1, 'n');
  printf("%s\n", lines[0]);
}
