#include "editor.h"
static void sighandler(int signo){
  if(signo == SIGQUIT){
  }
}

int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
}

int start(char * buff, int size){
  clear();
  scrollok(stdscr, TRUE);

  int row = 0;
  int col = 0;
  int maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);

  for (int i = 0; i < size; i++){
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
}

int movecursor(int x, int y, char ** lines, int maxy, int ch){
  if (ch == KEY_UP){
    if (y > 0){
      if (strlen(lines[y - 1]) == 1){
        if (2 > x){
          move(y - 1, x);
        }
      }
      else if(strlen(lines[y - 1]) > x){
        move(y - 1, x);
      }
    }
  }else if (ch == KEY_DOWN){
    if (y < maxy - 1){
      if (strlen(lines[y + 1]) == 1){
        if(strlen(lines[y + 1]) + 1> x){
          move(y + 1, x);
        }
      }
      else if (y < maxy - 1){
        if(strlen(lines[y + 1]) > x){
          move(y + 1, x);
        }
      }
    }
  }else if (ch == KEY_RIGHT){
    if (strlen(lines[y]) == 1){
      if (x < strlen(lines[y])){
        move(y, x + 1);
      }
    }
    else if (x < strlen(lines[y]) - 1){
      move(y, x + 1);
    }
  }else if (ch == KEY_LEFT){
    if(x > 0){
      move(y, x - 1);
    }
  }
  refresh();
}

int quit(char * buff, int size, int fd, char * filename){
  clear();
  printw("Are you sure you want to quit (Y/N)");
  refresh();
  while(1){
    int ch = getch();
    if(ch == 'y'){
      close(fd);
      fd = open(filename, O_WRONLY | O_TRUNC, 0666);
      write(fd, buff, size);
      endwin();
      exit(0);
    }else if (ch == 'n'){
      start(buff, size);
      break;
    }
  }
}

char * insert(char * line, int i, char ch){
  char * s1 = malloc(strlen(line) + 2);
  for (int k = 0; k < strlen(line) + 1; k++){
    if(k < i){
      s1[k] = line[k];
    }
    else if(k == i){
      s1[i] = ch;
    }else{
      s1[k] = line[k - 1];
    }
  }
  s1[strlen(line) + 1] = 0;
  return s1;
}

char * deletech(char * line, int i){
  char * s1 = malloc(strlen(line) + 1);
  if(strlen(line) == 0){
    s1[0] = '\0';
    return s1;
  }
  for (int k = 0; k < strlen(line) - 1; k++){
    if(k < i){
      s1[k] = line[k];
    }
    else{
      s1[k] = line[k  + 1];
    }
  }
  s1[strlen(line) + 1] = 0;
  return s1;
}

char * getnewbuff(char ** lines, int size, int buffsize){
  char * out = malloc(buffsize + 1);
  int curr = 0;
  for(int i = 0; i < size; i++){
    int len = strlen(lines[i]);
    for (int k = 0; k < len; k++){
      out[curr] = lines[i][k];
      curr++;
    }
    if(i < size - 1){
        out[curr] = '\n';
        curr++;
    }
  }
  out[curr] = '\0';
  return out;
}

char ** enterkey(char ** lines, int y, int x, int size){
  char ** out = malloc((size + 2) * sizeof(char *));
  for (int i = 0; i < size + 1; i++){
    if (i < y){
      out[i] = lines[i];
    }else if (i == y){
      char * line1 = malloc(strlen(lines[i]));
      char * line2 = malloc(strlen(lines[i]));
      for (int k = 0; k < strlen(lines[i]); k++){
        if(k < x){
          line1[k] = lines[i][k];
        }else{
          line2[k - x] = lines[i][k];
        }
      }
      line1[x] = '\0';
      line2[strlen(lines[i]) - x] = '\0';
      out[i] = line1;
      out[i + 1] = line2;
    }else{
      out[i + 1] = lines[i];
    }
  }
  out[size + 1] = NULL;
  return out;
}

void parse_args(char * line, char  ** arg_ary){
  char * token = calloc(1, sizeof(line) + 1);
  int size = 1;
  token = strsep(&line, " ");
  while (token != NULL){
    arg_ary[size - 1] = token;
    token = strsep(&line, " ");
    size++;
  }
  arg_ary[size - 1] = NULL;
}

int process(char * filename){
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
      newbuffsize++;
      newbuff = getnewbuff(lines, size, newbuffsize);
      start(newbuff, newbuffsize);
      move(y, x + 1);
    }else if (ch == KEY_BACKSPACE){
      if (x > 0){
        lines[y] = deletech(lines[y], x - 1);
        newbuffsize--;
        newbuff = getnewbuff(lines, size, newbuffsize);
        start(newbuff, newbuffsize);
        move(y, x - 1);
      }
    }else if (ch == KEY_ENTER || ch == '\n' || ch == '\r'){
      lines = enterkey(lines, y, x, size);
      size++;
      newbuff = getnewbuff(lines, size, newbuffsize);
      newbuffsize++;
      start(newbuff, newbuffsize);
      move(y + 1, 0);
    }
    movecursor(x,y,lines,size,ch);
  }
  endwin();
}
