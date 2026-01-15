#include "editor.h"
int main(){
  pid_t p;
  p = fork();
  if (p < 0){
    err();
  }else if (p == 0){
    char * args[16];
    char line[] = "ls";
    parse_args(line, args);
    execvp(args[0], args);
    err();
  }
  printf("Which file would you like to edit?:");
  char * filename = malloc(256);
  fgets(filename, 255, stdin);
  filename[strlen(filename) - 1] = 0;
  process(filename);
}
