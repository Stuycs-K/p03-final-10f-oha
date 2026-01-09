#include "editor.h"
int err(){
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
}

int start(char * buff, struct stat *statbuff){
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
}

int movecursor(int x, int y, char ** lines, int maxy, int ch){
  if (ch == KEY_UP){
    if (y == 0){
      return 0;
    }
    if (y > 0){
      if(strlen(lines[y - 1]) > x){
        move(y - 1, x);
      }
    }
  }else if (ch == KEY_DOWN){
    if(y == maxy){
      return 0;
    }
    if (y < maxy){
      if(strlen(lines[y + 1]) > x){
        move(y + 1, x);
      }
    }
  }else if (ch == KEY_RIGHT){
    if (x < strlen(lines[y]) - 1){
      move(y, x + 1);
    }
  }else if (ch == KEY_LEFT){
    if(x > 0){
      move(y, x - 1);
    }
  }
  refresh();
}

int quit(char * buff, struct stat *statbuff){
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
