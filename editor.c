#include "editor.h"
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
      if(strlen(lines[y - 1]) > x){
        move(y - 1, x);
      }
    }
  }else if (ch == KEY_DOWN){
    if (y == maxy - 2){
      if(strlen(lines[y + 1]) + 1> x){
        move(y + 1, x);
      }
    }
    else if (y < maxy - 1){
      if(strlen(lines[y + 1]) > x){
        move(y + 1, x);
      }
    }
  }else if (ch == KEY_RIGHT){
    if (y == maxy - 1){
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
  char * s1 = malloc(strlen(line));
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
